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
        if (0x3C <= address && address <= 0x3D) {
            printf("This probably is an SSD13xx OLED dot matrix display, "
                   "but it might be an HD44780 LCD character display with a PCF8574AT adapter.\n");
        } else if ((0x20 <= address && address <= 0x27) || (0x3A <= address && address <= 0x3F)) {
            // PCF8574T has address range 0x20-0x27; PCF8574AT has address range 0x3A-0x3F
            printf("This probably is an HD44780 LCD character display with a PCF8574 adapter.\n");
        }
    }
}

void loop(void) {}
