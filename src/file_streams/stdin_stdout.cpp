/**************************************************************************//**
 *
 * @file stdin_stdout.cpp
 *
 * @brief @copybrief cowpi_stdio_setup
 *
 * @copydetails cowpi_stdio_setup
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

#include "file_streams.h"
#include "file_streams_internal.h"

int8_t number_of_streams;
stream_data_t streams[MAXIMUM_NUMBER_OF_STREAMS];

#if defined(ARDUINO)

#include <Arduino.h>

#if defined (__AVR__)
static FILE serial_monitor_allocation;

static int cowpi_stdin_getc(FILE *filestream);

static int cowpi_stdout_putc(char c, FILE *filestream);

#endif //__AVR__

static int cowpi_arduinostream_get(void *cookie, char *buffer, int size);

static int cowpi_arduinostream_put(void *cookie, const char *buffer, int size);

void cowpi_stdio_setup(unsigned long bitrate) {
    Serial.begin(bitrate);
    do {
        delay(10);
    } while (!Serial);
    delay(10);
    FILE *serial_monitor;
#if defined (__AVR__)
    // use `fdev_setup_stream` instead of `fdevopen` to avoid `malloc`
    serial_monitor = &serial_monitor_allocation;
    fdev_setup_stream(serial_monitor, cowpi_stdout_putc, cowpi_stdin_getc, _FDEV_SETUP_RW);
#elif defined (ARDUINO_ARCH_SAMD) || defined (__MBED__)
    serial_monitor = funopen(&Serial, cowpi_arduinostream_get, cowpi_arduinostream_put, NULL, NULL);
    setlinebuf(serial_monitor);
#endif //architecture
    stdin = serial_monitor;
    stdout = serial_monitor;
}

/*
 * NOTES:
 * glibc and newlib expect the `get` function to return the number of characters read.
 * avr-libc expects the `getc` function to return the character read.
 * 
 * glibc and newlib expect the `put` function to return the number of characters written.
 * avr-libc expects the `putc` function to return 0 for success.
 * 
 * (https://www.gnu.org/software/libc/manual/html_node/Hook-Functions.html)
 * (https://sourceware.org/newlib/docs.html)
 * (https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html)
 */

#if defined (__AVR__)

static int cowpi_stdin_getc(__attribute__((unused)) FILE *filestream) {
    char c = '\0';
    cowpi_arduinostream_get(&Serial, &c, 1);
    return (int) c;
}

static int cowpi_stdout_putc(char c, __attribute__((unused)) FILE *filestream) {
    return !cowpi_arduinostream_put(&Serial, &c, 1);
}

#endif //__AVR__


static int cowpi_arduinostream_get(void *cookie, char *buffer, int size) {
    int number_of_available_bytes;
    while (!(number_of_available_bytes = ((Stream *) (cookie))->available())) {}
    int i = 0;
    while (i < size && i < number_of_available_bytes) {
        buffer[i] = (char) ((Stream *) (cookie))->read();
        // ((Stream *)(cookie))->print(buffer[i]);      // maybe we'll add an "echo" option later
        i++;
    }
    return i;
}

static int cowpi_arduinostream_put(void *cookie, const char *buffer, int size) {
    int i = 0;
    // we could just print the whole buffer at once,
    // but we want to insert CR with each LF
    while (i < size) {
        ((Stream *) (cookie))->print(buffer[i]);
        if (buffer[i] == '\n') {
            ((Stream *) (cookie))->print('\r');
        }
        i++;
    }
    return i;
}

#endif //ARDUINO