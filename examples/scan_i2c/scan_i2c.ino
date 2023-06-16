#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

void setup(void) {
    cowpi_stdio_setup(9600);
    pinMode(SDA, INPUT);
    pinMode(SCL, INPUT);

    int8_t address = cowpi_discover_i2c_address(SDA, SCL);
    if (address == 0) {
        printf("no devices detected\n");
    } else if (address == -1) {
        printf("multiple devices detected\n");
    } else {
        printf("device detected at %#04x\n", address);
    }
}

void loop(void) {}
