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
    OLED_MATRIX,
    MORSE_CODE
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

/**
 * Structure that consolidates all information needed about a display module.
 */
typedef struct {
    enum display_modules display_module;
    uint8_t width;                          // used by all displays except MORSE_CODE
    uint8_t height;                         // used by multi-row displays
    uint8_t words_per_minute;               // used by timed streams
    enum orientations orientation;          // used by LED matrix
} cowpi_display_module_t;

/**
 * Structure that consolidates all information needed to determine how data
 * should be sent to a display module.
 */
typedef struct {
    // C++ doesn't allow anonymous unions, so we'll be a little less memory-efficient
    enum protocols protocol;
    uint8_t data_pin;                       // used by all protocols (including NO_PROTOCOL)
    uint8_t clock_pin;                      // not used by NO_PROTOCOL
    uint8_t select_pin;                     // used only for SPI
    uint8_t i2c_address;                    // used only for I2C
    enum adapter_mappings adapter_mapping;  // used only for HD44780
} cowpi_display_module_protocol_t;

#ifdef __cplusplus
} // extern "C"

// While C++ will allow us to use a struct initializer that uses default (zero) values
// for fields that are not given an explicit initial value, it will not allow us to
// skip over fields when doing so -- cannot initialize i2c_address without explicitly
// (and unnecessarily) initilizing select_pin -- so we'll provide some initialization
// functions for use in C++ code.

static inline cowpi_display_module_protocol_t cowpi_configure_spi(uint8_t data_pin,
                                                                  uint8_t clock_pin,
                                                                  uint8_t select_pin,
                                                                  enum adapter_mappings adapter_mapping = COWPI_DEFAULT) {
    return (cowpi_display_module_protocol_t){
            .protocol = SPI,
            .data_pin = data_pin,
            .clock_pin = clock_pin,
            .select_pin = select_pin,
            .i2c_address = 0,
            .adapter_mapping = adapter_mapping
    };
}

static inline cowpi_display_module_protocol_t cowpi_configure_i2c(uint8_t data_pin,
                                                                  uint8_t clock_pin,
                                                                  uint8_t i2c_address,
                                                                  enum adapter_mappings adapter_mapping = COWPI_DEFAULT) {
    return (cowpi_display_module_protocol_t){
            .protocol = I2C,
            .data_pin = data_pin,
            .clock_pin = clock_pin,
            .select_pin = 0,
            .i2c_address = i2c_address,
            .adapter_mapping = adapter_mapping
    };
}
#endif //__CPLUSPLUS

#endif //COWPI_STDIO_TYPEDEFS_H
