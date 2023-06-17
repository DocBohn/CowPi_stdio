#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

#ifdef __MBED__
#define SDA PIN_WIRE_SDA
#define SCL PIN_WIRE_SCL
#endif

void setup(void) {
    cowpi_stdio_setup(9600);

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
