/**************************************************************************//**
 *
 * @file typedefs.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Structures that consolidate configuration data for display modules
 *      and protocols to communication with the display modules
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

#ifndef COWPI_STDIO_TYPEDEFS_H
#define COWPI_STDIO_TYPEDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Structure that consolidates all information needed to determine how data
 * should be sent to a display module.
 */
typedef struct {
    enum {
        UNSPECIFIED = 0,
        I2C,
        SPI
    } protocol;
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t select_pin;
} cowpi_display_module_protocol_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_TYPEDEFS_H
