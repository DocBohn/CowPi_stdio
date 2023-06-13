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

enum display_modules {
    NO_MODULE = 0,
    SEVEN_SEGMENT,
    LED_MATRIX,
    LCD_CHARACTER,
    OLED_MATRIX
};

enum orientations {
    EAST = 0,
    NORTH,
    WEST,
    SOUTH
};

enum protocols {
    NO_PROTOCOL = 0,
    I2C,
    SPI
};

enum adapter_mappings {
    COWPI_DEFAULT = 0,
    ADAFRUIT
};

typedef struct {
    enum display_modules display_module;
    enum orientations orientation;
    uint8_t width;
    uint8_t height;
} cowpi_display_module_t;

/**
 * Structure that consolidates all information needed to determine how data
 * should be sent to a display module.
 */
typedef struct {
    enum protocols protocol;
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t select_pin;                     // used only for SPI
    uint8_t i2c_address;                    // used only for I2C
    enum adapter_mappings adapter_mapping;  // used only for HD44780
} cowpi_display_module_protocol_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_TYPEDEFS_H
