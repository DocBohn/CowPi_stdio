/**************************************************************************//**
 *
 * @file display_module_file_streams.c
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

#include <stdint.h>
#include <avr/interrupt.h>
#include "file_streams_internal.h"


uint8_t buffer_head = 0;
uint8_t buffer_tail = 0;
symbol_t symbol_buffer[BUFFER_SIZE];


static void timer_handler(void) {
    static unsigned int milliseconds = 0;
    static unsigned int next_symbol_change = 1;
    if (!BUFFER_IS_EMPTY) {
        milliseconds++;
        if (next_symbol_change == milliseconds) {
            symbol_t *symbol = symbol_buffer + buffer_head;
            buffer_head = INCREMENT_MODULO(buffer_head, BUFFER_SIZE);
            symbol->callback(symbol);
            milliseconds = 0;
            next_symbol_change = symbol->symbol_duration * SYMBOL_DURATION_SCALING_FACTOR;
        }
    }
}

#if defined(__AVR_ATmega328P__) || defined (__AVR_ATmega2560__)
ISR(TIMER0_COMPB_vect) {
    timer_handler();
}
#endif //architecture