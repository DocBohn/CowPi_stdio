#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

#ifdef __AVR__
// strictly speaking, avr/pgmspace.h is included by Arduino.h and doesn't need to be explicitly included
#include <avr/pgmspace.h>

#endif //__AVR__

FILE *display;

void setup(void) {
    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(SS, OUTPUT);

    display = cowpi_add_display_module(
            (cowpi_display_module_t) {
                    .display_module = SEVEN_SEGMENT
            },
            (cowpi_display_module_protocol_t) {
                    .protocol = SPI,
                    .data_pin = MOSI,
                    .clock_pin = SCK,
                    .select_pin = SS
            }
    );
}

void loop(void) {
    // On AVR architectures, you can use `fprintf_P` with `PSTR` to put the
    // format string in flash memory, if you want to
#ifdef __AVR__
    fprintf_P(display, PSTR("Hello\n"));
#else
    fprintf(display, "Hello\n");
#endif //__AVR__
    delay(750);
    fprintf(display, "%8s\n", "World!");
    delay(750);
}