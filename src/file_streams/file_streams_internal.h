/**************************************************************************//**
 *
 * @file file_streams_internal.h
 *
 * @author Christopher A. Bohn
 *
 * @brief .....
 *
 * This file should be `#include`d *only* by .......
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

//#ifndef COWPI_STDIO_FILE_STREAMS_INTERNAL_H
//#define COWPI_STDIO_FILE_STREAMS_INTERNAL_H

#include "typedefs.h"

#ifdef COWPI_STDIO_FILE_STREAMS_INTERNAL

#ifdef __cplusplus
extern "C" {
#endif

// assumes the modulus is a power-of-two
#define INCREMENT_MODULO(value, modulus) (((value) + 1) & ((modulus) - 1))

#if defined(__AVR__)

typedef struct {
    FILE stream;

    int (*put)(void *cookie, const char *buffer, int size);

    cowpi_display_module_protocol_t configuration;
    uint8_t width;
    uint8_t height;
} stream_data_t;

#elif defined(ARDUINO_ARCH_SAMD) || defined(__MBED__)

typedef struct {
    cowpi_display_module_protocol_t configuration;
    uint8_t width;
    uint8_t height;
} stream_data_t;

#else
#error Unknown microcontroller architecture
#endif // architecture

#define MAXIMUM_NUMBER_OF_STREAMS 10
extern int8_t number_of_streams;
extern stream_data_t streams[MAXIMUM_NUMBER_OF_STREAMS];

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_FILE_STREAMS_INTERNAL

//#endif //COWPI_STDIO_FILE_STREAMS_INTERNAL_H