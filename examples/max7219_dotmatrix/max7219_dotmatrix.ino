#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

#ifdef __AVR__
// strictly speaking, avr/pgmspace.h is included by Arduino.h and doesn't need to be explicitly included
#include <avr/pgmspace.h>

#endif //__AVR__

FILE *no_scroll_display, *display;

void setup(void) {
    cowpi_stdio_setup(9600);
    display = cowpi_add_display_module(
            (cowpi_display_module_t) {
                    .display_module = LED_MATRIX,
                    .width = 8,
                    .height = 8,
                    .words_per_minute = 25,
                    .display_orientation = SOUTH,
                    .character_flip = HEADS
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
    fprintf_P(display, PSTR("Hello, World!\t"));
#else
    fprintf(no_scroll_display, "Hello, World!\t");
#endif //__AVR__
    fprintf(display, "Hello, World!\n");
}
