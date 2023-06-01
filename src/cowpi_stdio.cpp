/**************************************************************************//**
 *
 * @file cowpi_stdio.cpp
 *
 * @brief @copybrief cowpi_stdio.h
 *
 * @copydetails cowpi_stdio.h
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
#ifdef ARDUINO
#include <Arduino.h>

#ifdef __AVR__
static FILE serial_terminal;

static int cowpi_stdin_getc(FILE *stream);
static int cowpi_stdout_putc(char c, FILE *stream);
#endif //__AVR__


void cowpi_stdio_setup(unsigned long bitrate) {
    // stdin, stdout
    Serial.begin(bitrate);
    while (!Serial) {}
#ifdef __AVR__
    fdev_setup_stream(&serial_terminal, cowpi_stdout_putc, cowpi_stdin_getc, _FDEV_SETUP_RW);
    stdin = &serial_terminal;
    stdout = &serial_terminal;
}

static int cowpi_stdin_getc(__attribute__((unused)) FILE *stream) {
    while (!Serial.available()) {}
    return Serial.read();
}

static int cowpi_stdout_putc(char c, __attribute__((unused)) FILE *stream) {
    Serial.write(c);
    if (c == '\n') {
        Serial.write('\r');
    }
    return c;
#endif //__AVR__
}
#endif //ARDUINO
