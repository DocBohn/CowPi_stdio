/*!
 * @mainpage CowPi_stdio Library
 *
 * @version 0.4.2
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
 *      - ATmega328P (Arduino Uno, Arduino Nano)
 *      - ATmega2560 (Arduino Mega 2560)
 *      - ATmega4809 (Arduino Uno Wifi Rev 2, Arduino Nano Every)
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
 * @file cowpi_stdio.h
 *
 * @author Christopher A. Bohn
 *
 * @brief @copybrief cowpi_stdio_setup
 *
 * @copydetails cowpi_stdio_setup
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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Public-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configures the CowPi library to use `stdio.h` functions.
 *
 * Configures `stdout` and `stdin`, allowing programmers to use `printf()` to
 * write to, and `scanf()` to read from, the USB-based serial interface between
 * the microcontroller and the host computer.
 *
 * @ingroup configuration
 *
 * @param bitrate the UART bit rate
 */
void cowpi_stdio_setup(unsigned long bitrate);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_H
