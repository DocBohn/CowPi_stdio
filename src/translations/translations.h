//
// Created by Christopher Bohn on 6/17/23.
//

#ifndef COWPI_STDIO_TRANSLATIONS_H
#define COWPI_STDIO_TRANSLATIONS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ARDUINO_ARCH_AVR)
#define pin_number_t uint8_t
#define pin_mode_t uint8_t
#elif defined(ARDUINO_ARCH_MEGAAVR)
#define pin_number_t uint8_t
#define pin_mode_t PinMode
//#elif defined(ARDUINO_ARCH_SAMD) || defined (ARDUINO_ARCH_NRF52840) || defined (ARDUINO_ARCH_RP2040)
#elif defined(ARDUINO_ARCH_SAMD)
#define pin_number_t pin_size_t
#define pin_mode_t PinMode
#elif defined (ARDUINO_ARCH_MBED)
#define pin_number_t pin_size_t
#define pin_mode_t PinMode
#define SDA PIN_WIRE_SDA
#define SCL PIN_WIRE_SCL
#endif //ARCHITECTURE

void cowpi_pin_mode(pin_number_t pin, pin_mode_t mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_STDIO_TRANSLATIONS_H
