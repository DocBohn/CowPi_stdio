/**************************************************************************//**
 *
 * @file morse_code_streams.c
 *
 * @brief @copybrief .....
 *
 * @copydetails .....
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

#include <Arduino.h>
#include "file_streams_internal.h"
#include "../fonts/fonts.h"

#ifdef __AVR__

#include <util/delay.h>

#endif //__AVR__

static inline void inject_morse_symbol(symbol_t entry);

static void emit_morse_symbol(void *symbol);

int cowpi_morse_code_put(void *cookie, const char *buffer, int size) {
    stream_data_t *stream_data = (stream_data_t *) cookie;
    uint8_t pattern[18];
    uint8_t *symbols;
    int i = 0;
    while (i < size) {
        symbols = cowpi_font_ascii_to_morse_code(pattern, buffer[i]);
        uint8_t next_symbol;
        while ((next_symbol = *symbols++)) {
            int number_of_units;
            if (next_symbol == DIT || next_symbol == SYMBOL_SPACE) {
                number_of_units = 1;
            } else if (next_symbol == DAH || next_symbol == CHARACTER_SPACE) {
                number_of_units = 3;
            } else if (next_symbol == WORD_SPACE) {
                number_of_units = 7;
            } else {
                number_of_units = 0;
            }
            inject_morse_symbol((symbol_t) {
                    .callback = emit_morse_symbol,
                    .stream_data = stream_data,
                    .symbol = (next_symbol == DIT || next_symbol == DAH) ? 1 : 0,
                    .symbol_duration = number_of_units * stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
            });
            if (next_symbol == DIT || next_symbol == DAH) {
                // add intracharacter space
                inject_morse_symbol((symbol_t) {
                        .callback = emit_morse_symbol,
                        .stream_data = stream_data,
                        .symbol = 0,
                        .symbol_duration = stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
                });
            }
        }
        // add intercharacter space
        inject_morse_symbol((symbol_t) {
                .callback = emit_morse_symbol,
                .stream_data = stream_data,
                .symbol = 0,
                .symbol_duration = 3 * stream_data->ms_per_signal / SYMBOL_DURATION_SCALING_FACTOR
        });
        i++;
    }
    return i;
}

static inline void inject_morse_symbol(symbol_t entry) {
    while (BUFFER_IS_FULL) {
#ifdef __AVR__
        _delay_ms(1.0);     // busy-wait -- works even when interrupts are disabled
#else
        while(1);
#endif //__AVR__
    }
    symbol_buffer[buffer_tail] = entry;
    buffer_tail = INCREMENT_MODULO(buffer_tail, BUFFER_SIZE);
}

static void emit_morse_symbol(void *symbol) {
    symbol_t *symbol_data = (symbol_t *) symbol;
    uint8_t pin = symbol_data->stream_data->configuration.data_pin;
    uint8_t logic_level = symbol_data->symbol;
    digitalWrite(pin, logic_level);
}
