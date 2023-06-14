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
#include "spi.h"


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
