/**************************************************************************//**
 *
 * @file spi.c
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
#include "../fonts/fonts.h"
#include "../hd44780/hd44780.h"
#include "../max7219/max7219.h"
#include "../translations/translations.h"

#if defined(__AVR__)

static int cowpi_display_module_putc(char c, FILE *filestream);

#endif //__AVR__

static int cowpi_seven_segment_noscroll_put(void *cookie, const char *buffer, int size);

static int cowpi_lcd_character_put(void *cookie, const char *buffer, int size);

FILE *cowpi_add_display_module(cowpi_display_module_t display_module, cowpi_display_module_protocol_t configuration) {
    if (number_of_streams == MAXIMUM_NUMBER_OF_STREAMS) return NULL;
    if (configuration.protocol == I2C && configuration.i2c_address == 0) return NULL;
    FILE *stream;
    int (*put)(void *cookie, const char *buffer, int size);
    stream_data_t *stream_data = streams + number_of_streams;
    number_of_streams++;
    memcpy(&stream_data->configuration, &configuration, sizeof(cowpi_display_module_protocol_t));
    stream_data->width = display_module.width;
    stream_data->height = display_module.height;
    switch (stream_data->configuration.protocol) {
        case SPI:
            // pinMode(stream_data->configuration.data_pin, OUTPUT);
            // pinMode(stream_data->configuration.clock_pin, OUTPUT);
            // pinMode(stream_data->configuration.select_pin, OUTPUT);
            cowpi_pin_mode(stream_data->configuration.data_pin, OUTPUT);
            cowpi_pin_mode(stream_data->configuration.clock_pin, OUTPUT);
            cowpi_pin_mode(stream_data->configuration.select_pin, OUTPUT);
            break;
        case I2C:
            // pinMode(stream_data->configuration.data_pin, INPUT);
            // pinMode(stream_data->configuration.clock_pin, INPUT);
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
            put = cowpi_seven_segment_noscroll_put;
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
            put = cowpi_lcd_character_put;
            break;
        default:
            return NULL;
    }
#if defined(__AVR__)
    stream_data->put = put;
    stream = &(stream_data->stream);
    fdev_setup_stream(stream, cowpi_display_module_putc, NULL, _FDEV_SETUP_WRITE);
#elif defined (ARDUINO_ARCH_SAMD) || defined (__MBED__)
    stream = funopen(stream_data, NULL, put, NULL, NULL);
    // I suppose we should make line buffering an option, but not today
    if (setvbuf(stream, NULL, _IONBF, 0)) return NULL;
#else
    stream = NULL;
#endif //architecture
    return stream;
}

#if defined(__AVR__)

static int cowpi_display_module_putc(char c, FILE *filestream) {
    // because the file stream is the first element in the struct,
    // the address of that element is also the base address of the struct
    stream_data_t *stream_data = (stream_data_t *) filestream;
    return !stream_data->put(stream_data, &c, 1);
}

#endif //__AVR__

static int cowpi_seven_segment_noscroll_put(void *cookie, const char *buffer, int size) {
    stream_data_t *stream_data = (stream_data_t *) cookie;
    static int8_t left_to_right_position = 0;
    uint8_t pattern;
    int i = 0;
    char c = buffer[i];
    while (i < size && left_to_right_position < stream_data->width) {
        // TODO: handle other control sequences
        if (c == '\n') {
            pattern = cowpi_font_ascii_to_7segment(' ');
            while (left_to_right_position < stream_data->width) {
                cowpi_max7219_send(&stream_data->configuration, stream_data->width - left_to_right_position, pattern);
                left_to_right_position++;
            }
        } else {
            pattern = cowpi_font_ascii_to_7segment(c);
            cowpi_max7219_send(&stream_data->configuration, stream_data->width - left_to_right_position, pattern);
            left_to_right_position++;
            c = buffer[i];
        }
        i++;
    }
    if (c == '\n' && left_to_right_position == stream_data->width) {
        left_to_right_position = 0;
    }
    return i;
}

// "print" BEL (\a, 0x07) since 0x07 is a custom character location
// "print" BS (\b, 0x08) since 0x08 is a custom character location
// HT/TAB (\t, 0x09) advances 1 space without overwriting the character
// LF/NL (\n, 0x0A) clears the remaining characters, advances to the next row (or the first row), and performs a carriage return
// VT (\v, 0x0B) advances to the next row (or the first row) without clearing any characters, and performs a carriage return
// FF/NP (\f, 0x0C) places the cursor in the top row and performs a carriage return
// CR (\r, 0x0D) places the cursor at the left position of the current row
// "print" ESC (\e, 0x1B) since 0x1B is a printable character for ROM Code A00
// "print" DEL (0x7F) since 0x7F is a printable character for both ROM Codes
static int cowpi_lcd_character_put(void *cookie, const char *buffer, int size) {
    stream_data_t *stream_data = (stream_data_t *) cookie;
    uint8_t width = stream_data->width;
    uint8_t height = stream_data->height;
    static uint8_t ddram_address = 0;
    static int8_t row = 0;
    static const uint8_t row_starts[] = {0x00, 0x40, 0x14, 0x54};
    static bool scrolled = false;
    int i = 0;
    while (i < size) {
        char c = buffer[i];
        uint8_t row_start = row_starts[row];
        if (ddram_address == row_start) {
            cowpi_hd44780_place_cursor(&stream_data->configuration, ddram_address);
        }
        switch (c) {
            case '\n':
                if (!scrolled) {
                    while (ddram_address < row_start + width) {
                        cowpi_hd44780_send_character(&stream_data->configuration, ' ');
                        ddram_address++;
                    }
                }
                /* FALLTHROUGH */
            case '\v':
                if (!scrolled) {
//                    row = (row == height - 1) ? 0 : row + 1;
                    row = INCREMENT_MODULO(row, height);
                    row_start = row_starts[row];
                }
                /* FALLTHROUGH */
            case '\r':
                ddram_address = row_start;
                scrolled = false;
                break;
            case '\f':
                row = 0;
                ddram_address = row_starts[row];
                scrolled = false;
                break;
            case '\t':
                ddram_address++;
                if (ddram_address == row_start + width) {
                    scrolled = true;
//                    row = (row == height - 1) ? 0 : row + 1;
                    row = INCREMENT_MODULO(row, height);
                    ddram_address = row_starts[row];
                } else {
                    scrolled = false;
                }
                cowpi_hd44780_place_cursor(&stream_data->configuration, ddram_address);
                break;
            default:    // I'm breaking my rule about using `default` only for error cases
                cowpi_hd44780_send_character(&stream_data->configuration, c);
                ddram_address++;
                if (ddram_address == row_start + width) {
                    scrolled = true;
//                    row = (row == height - 1) ? 0 : row + 1;
                    row = INCREMENT_MODULO(row, height);
                    ddram_address = row_starts[row];
                    cowpi_hd44780_place_cursor(&stream_data->configuration, row_start);
                } else {
                    scrolled = false;
                }
        }
        i++;
    }
    return i;
}
