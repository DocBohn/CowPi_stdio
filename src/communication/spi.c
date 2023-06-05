/**************************************************************************//**
 *
 * @file spi.c
 *
 * @brief @copybrief spi.h
 *
 * @copydetails spi.h
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

#include <Arduino.h>
#include <stdint.h>
#include "spi.h"


/** @private */
uint8_t cowpi_reverse_byte(uint8_t byte) {
    uint8_t reversed_byte = 0;
    // strike a balance:
    // - one bit at a time requires 1 case, 8 iterations
    // - two bits at a time requires 4 cases, 4 iterations
    // - four bits at a time requires 16 cases, 2 iterations
    // - eight bits at a time requires 256 cases, 1 iteration
    for (int i = 0; i < 4; i++) {
        uint8_t quarter_byte = byte & 0x03;
        byte >>= 2;
        reversed_byte >>= 2;
        switch (quarter_byte) {
            case 0x0:
                reversed_byte |= 0x00;
                break;
            case 0x1:
                reversed_byte |= 0x80;
                break;
            case 0x2:
                reversed_byte |= 0x40;
                break;
            case 0x3:
                reversed_byte |= 0xC0;
                break;
            default:
//                unreachable();              // C23
                __builtin_unreachable();    // gcc
//                assert(false);              // better than nothing
        }
    }
    return reversed_byte;
}

static uint8_t data_pin;
static uint8_t clock_pin;
static bit_order_t data_order;

void (*cowpi_spi_initialize)(const cowpi_display_module_protocol_t *configuration,
                             bit_order_t bit_order) = cowpi_spi_initialize_bitbang;

void (*cowpi_spi_transmit)(uint8_t byte) = cowpi_spi_transmit_bitbang;

void (*cowpi_spi_finalize)(void) = cowpi_spi_finalize_bitbang;

void cowpi_spi_initialize_bitbang(const cowpi_display_module_protocol_t *configuration, bit_order_t bit_order) {
    data_pin = configuration->data_pin;
    clock_pin = configuration->clock_pin;
    data_order = bit_order;
}

void cowpi_spi_transmit_bitbang(uint8_t byte) {
    shiftOut(data_pin, clock_pin, data_order == MSB_FIRST ? MSBFIRST : LSBFIRST, byte);
}

void cowpi_spi_finalize_bitbang(void) { ; }

void cowpi_spi_initialize_hardware(__attribute__((unused)) const cowpi_display_module_protocol_t *configuration,
                                   bit_order_t bit_order) {
#ifdef __AVR__
    uint8_t bit_order_bit = ((bit_order == LSB_FIRST) << DORD);
    /* Enable SPI, data order, Controller, set clock rate fck/16 [1MHz] */
    SPCR = (1 << SPE) | bit_order_bit | (1 << MSTR) | (1 << SPR0);
    /* By repeating myself, both constants will be generated at compile time */
#endif //__AVR__
}

void cowpi_spi_transmit_hardware(uint8_t byte) {
#ifdef __AVR__
    SPDR = byte;
    while (!(SPSR & 0x80)) {}
#endif //__AVR__
}

void cowpi_spi_finalize_hardware(void) {
#ifdef __AVR__
    SPCR = 0;
#endif //__AVR__
}
