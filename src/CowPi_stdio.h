/*!
 * @mainpage CowPi_stdio Library
 *
 * @version 0.4.3
 *
 * @copyright (c) 2022-23 Christopher A. Bohn
 *
 * @section overview Overview
 *
 * This library is designed to support the use of idiomatic C input/output
 * functions with microcontroller boards.
 *
 * @section hardware Supported Hardware
 *
 * The current version supports:
 *  - Microcontrollers
 *      - ATmega328P    (Arduino Uno, Arduino Nano)
 *      - ATmega2560    (Arduino Mega 2560)
 *      - ATmega4809    (Arduino Uno Wifi Rev 2, Arduino Nano Every)
 *      - RP2040        (Raspberry Pi Pico (Arduino Framework),
 *                       Arduino Nano RP2040 Connect)
 *      - SAM D21       (Arduino Zero, Arduino Nano 33 IoT)
 *  - Display modules
 *      - MAX7219-based 8-digit, 7-segment display
 *
 * @section license License
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

/**************************************************************************//**
 *
 * @file CowPi_stdio.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions to configure file streams for `stdio.h` functions.
 *
 * Configures the `stdin` and `stdout` streams to work with the Arduino Serial
 * Monitor. Configures display modules and provides file streams to display text
 * on those display modules using `fprintf()`.
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

#ifndef COWPI_STDIO_H
#define COWPI_STDIO_H

/* Public-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
    
#include "typedefs.h"
#include "communication/communication.h"
#include "hd44780/hd44780.h"
#include "fonts/fonts.h"
#include "max7219/max7219.h"

/**
 * @brief Configures the "Serial Monitor" for `printf()` and `scanf()`.
 *
 * Configures `stdout` and `stdin`, allowing programmers to use `printf()` to
 * write to, and `scanf()` to read from, the USB-based serial interface between
 * the microcontroller and the host computer.
 *
 * @ingroup configuration
 *
 * @param bitrate the serial interface's bit rate
 */
void cowpi_stdio_setup(unsigned long bitrate);

/**
 * @brief Configures a display module for `fprintf()`.
 * 
 * @param display_module the display module's details
 * @param configuration the communication protocol's details
 * @return a pointer to a `FILE` stream for the display module
 */
FILE *cowpi_add_display_module(cowpi_display_module_t display_module, cowpi_display_module_protocol_t configuration);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_H
