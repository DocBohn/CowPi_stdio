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

#include "CowPi_stdio.h"
#include "typedefs.h"
#include "fonts/fonts.h"
#include "max7219/max7219.h"

#if defined(__AVR__)

static int cowpi_display_module_putc(char c, FILE *filestream);

typedef struct {
    FILE stream;

    int (*put)(void *cookie, const char *buffer, int size);

    cowpi_display_module_protocol_t configuration;
    uint8_t width;
} stream_data_t;

#elif defined(ARDUINO_ARCH_SAMD) || defined(__MBED__)

typedef struct {
    cowpi_display_module_protocol_t configuration;
    uint8_t width;
} stream_data_t;

#else
#error Unknown microcontroller architecture
#endif // architecture

static cowpi_display_module_protocol_t *copy_cowpi_display_module_protocol(cowpi_display_module_protocol_t *destination,
                                                                           const cowpi_display_module_protocol_t *source);

static int cowpi_seven_segment_noscroll_put(void *cookie, const char *buffer, int size);

#define MAXIMUM_NUMBER_OF_STREAMS 10
static int8_t number_of_streams = 0;
static stream_data_t streams[MAXIMUM_NUMBER_OF_STREAMS];

FILE *cowpi_add_display_module(cowpi_display_module_t display_module, cowpi_display_module_protocol_t configuration) {
    if (number_of_streams == MAXIMUM_NUMBER_OF_STREAMS) return NULL;
    FILE *stream;
    int (*put)(void *cookie, const char *buffer, int size);
    stream_data_t *stream_data = streams + number_of_streams;
    number_of_streams++;
    copy_cowpi_display_module_protocol(&stream_data->configuration, &configuration);
    if (display_module.display_module == SEVEN_SEGMENT) {
        if (stream_data->configuration.protocol != SPI) return NULL;
        if (!display_module.width) display_module.width = 8;
        if (display_module.width != 8) return NULL;
        stream_data->width = display_module.width;
        cowpi_setup_max7219(&stream_data->configuration);
        put = cowpi_seven_segment_noscroll_put;
    } else {
        return NULL;
    }
#if defined(__AVR__)
    stream_data->put = put;
    stream = &(stream_data->stream);
    fdev_setup_stream(stream, cowpi_display_module_putc, NULL, _FDEV_SETUP_WRITE);
#elif defined (ARDUINO_ARCH_SAMD) || defined (__MBED__)
    stream = funopen(stream_data, NULL, put, NULL, NULL);
#endif //architecture
    return stream;
}

static cowpi_display_module_protocol_t *copy_cowpi_display_module_protocol(cowpi_display_module_protocol_t *destination,
                                                                           const cowpi_display_module_protocol_t *source) {
    destination->protocol = source->protocol;
    destination->data_pin = source->data_pin;
    destination->clock_pin = source->clock_pin;
    destination->select_pin = source->select_pin;
    return destination;
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
