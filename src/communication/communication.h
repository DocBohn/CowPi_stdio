/**************************************************************************//**
 *
 * @file communication.h
 *
 * @brief Public-facing type definitions and function pointers for SPI & I2C.
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

#ifndef COWPI_STDIO_COMMUNICATION_H
#define COWPI_STDIO_COMMUNICATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "../typedefs.h"

typedef enum {
    LSB_FIRST,
    MSB_FIRST
} bit_order_t;


/**
 * Function pointer for function that takes care of any setup needed before
 * using SPI to send data to a display module. The particulars of what this
 * setup is depends on the particular SPI implementation.
 *
 * @param configuration the pins used for SPI
 * @param bit_order indicates whether the peripheral expects the byte to arrive
 *      LSB first or MSB first
 *
 * @sa cowpi_spi_transmit
 * @sa cowpi_spi_finalize
 */
extern void (*cowpi_spi_initialize)(const cowpi_display_module_protocol_t *configuration, bit_order_t bit_order);

/**
 * Function pointer for function that uses SPI to send data to a display module.
 * This might be a pre-defined implementation that uses the microcontroller's
 * SPI hardware, or it might be a pre-defined bit-bang implementation.
 *
 * @param byte the byte to be transmitted to the peripheral
 *
 * @sa cowpi_spi_initialize
 * @sa cowpi_spi_finalize
 */
extern void (*cowpi_spi_transmit)(uint8_t byte);

/**
 * Function pointer for function that takes care of any teardown needed after
 * using SPI to send data to a display module. The particulars of what this
 * teardown is depends on the particular SPI implementation.
 *
 * @sa cowpi_spi_initialize
 * @sa cowpi_spi_transmit
 */
extern void (*cowpi_spi_finalize)(void);


/**
 * Function pointer for function that takes care of any setup needed before
 * using I2C to send data to a display module. This includes, but might not
 * be limited to, transmitting the start bit and the peripheral's address.
 *
 * @param configuration the microcontroller pins, adapter mapping, and possibly
 *      i2c peripheral address
 *
 * @sa cowpi_i2c_transmit
 * @sa cowpi_i2c_finalize
 */
extern void (*cowpi_i2c_initialize)(const cowpi_display_module_protocol_t *configuration);

/**
 * Function pointer for function that uses SPI to send data to a display module.
 * This might be a pre-defined implementation that uses the microcontroller's
 * SPI hardware, or it might be a pre-defined bit-bang implementation.
 *
 * @param byte the byte to be transmitted to the peripheral
 * @return <code>true</code> if ACK received; <code>false</code> otherwise
 *
 * @sa cowpi_i2c_initialize
 * @sa cowpi_i2c_finalize
 */
extern bool (*cowpi_i2c_transmit)(uint8_t byte);

/**
 * Function pointer for function that takes care of any teardown needed after
 * using SPI to send data to a display module. This includes, but might not
 * be limited to, transmitting the stop bit.
 *
 * @sa cowpi_i2c_initialize
 * @sa cowpi_i2c_transmit
 */
extern void (*cowpi_i2c_finalize)(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_COMMUNICATION_H
