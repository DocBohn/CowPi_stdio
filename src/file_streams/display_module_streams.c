/**************************************************************************//**
 *
 * @file display_module_streams.c
 *
 * @brief @copybrief cowpi_add_display_module
 *
 * @copydetails cowpi_add_display_module
 *
 ******************************************************************************/

/* CowPi_stdio (c) 2022-23 Christopher A. Bohn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define COWPI_STDIO_FILE_STREAMS_INTERNAL

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include "file_streams.h"
#include "file_streams_internal.h"
#include "../hd44780/hd44780.h"
#include "../max7219/max7219.h"
#include "../translations/translations.h"

int8_t number_of_streams;
stream_data_t streams[MAXIMUM_NUMBER_OF_STREAMS];

#if defined(__AVR__)

static int cowpi_display_module_putc(char c, FILE *filestream);

#endif //__AVR__

FILE *cowpi_add_display_module(cowpi_display_module_t display_module, cowpi_display_module_protocol_t configuration) {
    if (number_of_streams == MAXIMUM_NUMBER_OF_STREAMS) return NULL;
    if (configuration.protocol == I2C && configuration.i2c_address == 0) return NULL;
    FILE *stream;
    stream_data_t *stream_data = streams + number_of_streams;
    memcpy(&stream_data->configuration, &configuration, sizeof(cowpi_display_module_protocol_t));
    stream_data->width = display_module.width;
    stream_data->height = display_module.height;
    switch (stream_data->configuration.protocol) {
        case NO_PROTOCOL:
            if (display_module.display_module != MORSE_CODE) return NULL;
            cowpi_pin_mode(stream_data->configuration.data_pin, OUTPUT);
            break;
        case SPI:
            cowpi_pin_mode(stream_data->configuration.data_pin, OUTPUT);
            cowpi_pin_mode(stream_data->configuration.clock_pin, OUTPUT);
            cowpi_pin_mode(stream_data->configuration.select_pin, OUTPUT);
            break;
        case I2C:
            cowpi_pin_mode(stream_data->configuration.data_pin, INPUT);
            cowpi_pin_mode(stream_data->configuration.clock_pin, INPUT);
            break;
        default:
            return NULL;
    }
    switch (display_module.display_module) {
        case SEVEN_SEGMENT:
            // default to a single module of 8 digits (which is good because we're not handling chained modules yet)
            if (!stream_data->width) stream_data->width = 8;
            // must use SPI
            if (stream_data->configuration.protocol != SPI) return NULL;
            // number of digits must be multiple of 8
            if (display_module.width & 0x7) return NULL;
            cowpi_setup_max7219(&stream_data->configuration);
            stream_data->put = cowpi_seven_segment_noscroll_put;
            break;
        case LCD_CHARACTER:
            // default to the "native" LCD1602
            if (!stream_data->width) stream_data->width = 16;
            if (!stream_data->height) stream_data->height = 2;
            // must be LCD1602 or LCD2004
            if (!(stream_data->width == 16 && stream_data->height == 2)
                && !(stream_data->width == 20 && stream_data->height == 4))
                return NULL;
            cowpi_setup_hd44780(&stream_data->configuration);
            cowpi_hd44780_set_backlight(&stream_data->configuration, 1);
            stream_data->put = cowpi_lcd_character_put;
            break;
        case MORSE_CODE:
#if defined(__AVR_ATmega328P__) || defined (__AVR_ATmega2560__)
            OCR0B = 0x40;   // fires every 1.024ms -- close enough
            TIMSK0 |= (1 << OCIE0B);
#endif //architecture
            uint8_t words_per_minute = display_module.words_per_minute;
            // default to 12wpm
            if (!words_per_minute) words_per_minute = 5;
            // minimum 1wpm (1200ms per unit), maximum 50wpm (24ms per unit)
            if (words_per_minute > 50) words_per_minute = 50;
            stream_data->ms_per_signal = 60000 /* ms per minute */ / 50 /* units per "PARIS" word */ / words_per_minute;
            stream_data->put = cowpi_morse_code_put;
            break;
        default:
            return NULL;
    }
#if defined(__AVR__)
    stream = &(streams[number_of_streams].stream);
    fdev_setup_stream(stream, cowpi_display_module_putc, NULL, _FDEV_SETUP_WRITE);
#elif defined (ARDUINO_ARCH_SAMD) || defined (__MBED__)
    stream = funopen(stream_data, NULL, stream_data->put, NULL, NULL);
    // I suppose we should make line buffering an option, but not today
    if (setvbuf(stream, NULL, _IONBF, 0)) return NULL;
    stream_data->stream = stream;
#else
    stream = NULL;
#endif //architecture
    number_of_streams++;
    return stream;
}

#if defined(__AVR__)

static int cowpi_display_module_putc(char c, FILE *filestream) {
    // because the file stream is the first element in the struct,
    // the address of that element is also the base address of the struct
    stream_data_t *stream_data = cowpi_file_to_cookie(filestream);
    return !stream_data->put(stream_data, &c, 1);
}

#endif //__AVR__

stream_data_t *cowpi_file_to_cookie(FILE *filestream) {
#ifdef __AVR__
    // because the file stream is the first element in the struct,
    // the address of that element is also the base address of the struct
    return (stream_data_t *) filestream;
#else
    stream_data_t *cookie = NULL;
    int i = 0;
    while (cookie == NULL && i < MAXIMUM_NUMBER_OF_STREAMS) {
        if (streams[i].stream == filestream) {
            cookie = streams + i;
        } else {
            i++;
        }
    }
    return cookie;
#endif //__AVR__
}

void cowpi_clear_display(FILE *filestream) {
    stream_data_t *stream_data = cowpi_file_to_cookie(filestream);
    int (*put)(void *, const char *, int) = stream_data->put;
    cowpi_display_module_protocol_t *configuration = &stream_data->configuration;
    if (put == cowpi_seven_segment_noscroll_put) {
        fprintf(filestream, "\r\n");    // place cursor at start of line, and then \n clears it
    } else if (put == cowpi_lcd_character_put) {
        fprintf(filestream, "\f");      // so that `put` knows where the cursor is
        cowpi_hd44780_clear_display(configuration);
    } else {}
}

void cowpi_sleep_display(FILE *filestream) {
    stream_data_t *stream_data = cowpi_file_to_cookie(filestream);
    int (*put)(void *, const char *, int) = stream_data->put;
    cowpi_display_module_protocol_t *configuration = &stream_data->configuration;
    if (put == cowpi_seven_segment_noscroll_put) {
        cowpi_max7219_shutdown(configuration);
    } else if (put == cowpi_lcd_character_put) {
        cowpi_hd44780_set_backlight(configuration, false);
    } else {}
}

void cowpi_wake_display(FILE *filestream) {
    stream_data_t *stream_data = cowpi_file_to_cookie(filestream);
    int (*put)(void *, const char *, int) = stream_data->put;
    cowpi_display_module_protocol_t *configuration = &stream_data->configuration;
    if (put == cowpi_seven_segment_noscroll_put) {
        cowpi_max7219_startup(configuration);
    } else if (put == cowpi_lcd_character_put) {
        cowpi_hd44780_set_backlight(configuration, true);
    } else {}
}
