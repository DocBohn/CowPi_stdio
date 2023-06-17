//
// Created by Christopher Bohn on 6/17/23.
//

#include "translations.h"

extern "C" {

void cowpi_pin_mode(pin_number_t pin, pin_mode_t mode) {
    pinMode(pin, mode);
}

}