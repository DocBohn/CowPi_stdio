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

#include <stdio.h>
#include "typedefs.h"

#ifdef COWPI_STDIO_FILE_STREAMS_INTERNAL

#ifdef __cplusplus
extern "C" {
#endif

// assumes the modulus is a power-of-two
#define INCREMENT_MODULO(value, modulus) (((value) + 1) & ((modulus) - 1))

typedef struct {
#if defined(__AVR__)
    FILE stream;    // for AVR, we'll use the FILE's address to refer back to the stream_data_t, a frequent need
#else
    FILE *stream;   // for ARM, we'll have to compare addresses for occasionally finding a FILE's stream_data_t
#endif //__AVR__
    int (*put)(void *cookie, const char *buffer, int size);
    cowpi_display_module_protocol_t configuration;
    uint8_t width;
    uint8_t height;
    uint16_t ms_per_signal;
} stream_data_t;

#define MAXIMUM_NUMBER_OF_STREAMS (5)
extern int8_t number_of_streams;
extern stream_data_t streams[MAXIMUM_NUMBER_OF_STREAMS];


typedef struct {
    void (*callback)(void *symbol);
    stream_data_t *stream_data;
    uint8_t symbol;
    uint8_t symbol_duration;
} symbol_t;

// BUFFER_SIZE needs to be power-of-two to work with INCREMENT_MODULO
// A larger buffer reduces likelihood of blocking, but ATmega328P has only 2KB of RAM to work with
#if defined(__AVR_ATmega328P__)
#define BUFFER_SIZE (16)
// ATmega4809 has 6KB, and ATmega2560 has 8KB
#elif defined (__AVR_ATmega2560__) || defined (__AVR_ATmega4809__)
#define BUFFER_SIZE (32)
// RA4M1 has 32KB, SAMD21 & nRF52840 have 256KB, and RP24040 has 264KB
#else
#define BUFFER_SIZE (128)
#endif
extern uint8_t buffer_head;
extern uint8_t buffer_tail;
extern symbol_t symbol_buffer[BUFFER_SIZE];
#define BUFFER_IS_EMPTY ((buffer_head) == (buffer_tail))
#define BUFFER_IS_FULL  ((INCREMENT_MODULO(buffer_tail, BUFFER_SIZE)) == (buffer_head))
#define BUFFER_HAS_ROOM_FOR(quantity)
#define SYMBOL_DURATION_SCALING_FACTOR (8)



stream_data_t *cowpi_file_to_cookie(FILE *filestream);


/**
 * .......
 * @param cookie
 * @param buffer
 * @param size
 * @return
 */
int cowpi_seven_segment_noscroll_put(void *cookie, const char *buffer, int size);

/**
 * .......
 * @param cookie
 * @param buffer
 * @param size
 * @return
 */
int cowpi_lcd_character_put(void *cookie, const char *buffer, int size);

/**
 * .......
 * @param cookie
 * @param buffer
 * @param size
 * @return
 */
int cowpi_morse_code_put(void *cookie, const char *buffer, int size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_FILE_STREAMS_INTERNAL

//#endif //COWPI_STDIO_FILE_STREAMS_INTERNAL_H
