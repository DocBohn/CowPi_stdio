/**************************************************************************//**
 *
 * @file max7219_streams.c
 *
 * @brief @copybrief cowpi_seven_segment_noscroll_put
 *
 * @copydetails cowpi_seven_segment_noscroll_put
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
#include <stdint.h>
#include <stdio.h>
#include "file_streams_internal.h"
#include "../fonts/fonts.h"
#include "../max7219/max7219.h"

static void send_segment_pattern_from_buffer(void *symbol);

int cowpi_seven_segment_noscroll_put(void *cookie, const char *buffer, int size) {
    stream_data_t *stream_data = (stream_data_t *) cookie;
    static int8_t left_to_right_position = 0;
    static bool escaped = false;
    uint8_t pattern;
    int i = 0;
    while (i < size) {
        if (escaped) {
            pattern = buffer[i];
            if (left_to_right_position < stream_data->width) {
                cowpi_max7219_send(&stream_data->configuration,
                                   stream_data->width - left_to_right_position,
                                   pattern);
                left_to_right_position++;
            }
            escaped = false;
        } else {
            char c = buffer[i];
            switch (c) {
                case 0x1B:
                    escaped = true;
                    break;
                case '\a':
                    break;
                case '\n':
                    pattern = cowpi_font_ascii_to_7segment(' ');
                    while (left_to_right_position < stream_data->width) {
                        cowpi_max7219_send(&stream_data->configuration,
                                           stream_data->width - left_to_right_position,
                                           pattern);
                        left_to_right_position++;
                    }
                    /* FALLTHROUGH */
                case '\v':  // with only one row, there's not much vertical movement going on
                case '\r':
                case '\f':
                    left_to_right_position = 0;
                    break;
                case '\b':
                    if (left_to_right_position > 0) {
                        left_to_right_position--;
                    }
                    break;
                case 0x7F:
                    if (left_to_right_position > 0) {
                        left_to_right_position--;
                        pattern = cowpi_font_ascii_to_7segment(' ');
                        cowpi_max7219_send(&stream_data->configuration,
                                           stream_data->width - left_to_right_position,
                                           pattern);
                    }
                    break;
                case '\t':
                    if (left_to_right_position < stream_data->width) {
                        left_to_right_position++;
                    }
                    break;
                default:    // I'm breaking my rule about using `default` only for error cases
                    pattern = cowpi_font_ascii_to_7segment(c);
                    if (left_to_right_position < stream_data->width) {
                        cowpi_max7219_send(&stream_data->configuration,
                                           stream_data->width - left_to_right_position,
                                           pattern);
                        left_to_right_position++;
                    }
            }
        }
        i++;
    }
    return i;
}

int cowpi_seven_segment_scrolling_put(void *cookie, const char *buffer, int size) {
    stream_data_t *stream_data = (stream_data_t *) cookie;
    static bool escaped = false;
    uint8_t pattern;
    int i = 0;
    while (i < size) {
        if (escaped) {
            pattern = buffer[i];
            add_symbol_to_buffer((symbol_t) {
                    .callback = send_segment_pattern_from_buffer,
                    .stream_data = stream_data,
                    .symbol = pattern,
                    .symbol_duration = stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
            });
            escaped = false;
        } else {
            char c = buffer[i];
            switch (c) {
                case 0x1B:
                    escaped = true;
                    break;
                case '\a':
                case '\b':
                case 0x7F:
                    break;
                case '\v':
                case '\r':
                case '\f':
                case '\n':
                    pattern = cowpi_font_ascii_to_7segment(' ');
                    uint8_t width = stream_data->width;
                    for (int j = 0; j < width; j++) {
                        add_symbol_to_buffer((symbol_t) {
                                .callback = send_segment_pattern_from_buffer,
                                .stream_data = stream_data,
                                .symbol = pattern,
                                .symbol_duration = stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
                        });
                    }
                    break;
                case '\t':
                    pattern = cowpi_font_ascii_to_7segment(' ');
                    for (int j = 0; j < 4; j++) {
                        add_symbol_to_buffer((symbol_t) {
                                .callback = send_segment_pattern_from_buffer,
                                .stream_data = stream_data,
                                .symbol = pattern,
                                .symbol_duration = stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
                        });
                    }
                    break;
                default:    // I'm breaking my rule about using `default` only for error cases
                    pattern = cowpi_font_ascii_to_7segment(c);
                    add_symbol_to_buffer((symbol_t) {
                            .callback = send_segment_pattern_from_buffer,
                            .stream_data = stream_data,
                            .symbol = pattern,
                            .symbol_duration = stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
                    });
            }
        }
        i++;
    }
    return i;
}

static void send_segment_pattern_from_buffer(void *symbol) {
    static uint8_t display_patterns[8] = {0};   // for now, use 8 -- will have to put an upper limit on it later
    symbol_t *symbol_data = (symbol_t *) symbol;
    cowpi_display_module_protocol_t *configuration = &symbol_data->stream_data->configuration;
    uint8_t width = symbol_data->stream_data->width;
    for (int i = width - 1; i >= 0; i--) {
        if (i > 0) {
            display_patterns[i] = display_patterns[i - 1];
        } else {
            display_patterns[i] = symbol_data->symbol;
        }
        cowpi_max7219_send(configuration, i + 1, display_patterns[i]);
    }
}
