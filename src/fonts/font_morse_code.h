/**************************************************************************//**
 *
 * @file font_morse_code.h
 *
 * @author Christopher A. Bohn
 *
 * @brief .......
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

#ifndef COWPI_STDIO_FONT_MORSE_CODE_H
#define COWPI_STDIO_FONT_MORSE_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum {
    END_OF_CHARACTER = 0,
    SYMBOL_SPACE,       // 1 unit
    CHARACTER_SPACE,    // 3 units
    WORD_SPACE,         // 7 units
    DIT,                // 1 unit
    DAH                 // 3 units
};

/**
 * @brief ...
 *
 * ...
 *
 * @ingroup font
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose ......... is
 *      to be provided
 * @return              `destination`, with the requested........
 */
uint8_t *cowpi_font_ascii_to_morse_code(uint8_t *destination, char c);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_FONT_MORSE_CODE_H
