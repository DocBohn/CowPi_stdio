#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

#ifdef __AVR__
// strictly speaking, avr/pgmspace.h is included by Arduino.h and doesn't need to be explicitly included
#include <avr/pgmspace.h>

#endif //__AVR__

FILE *no_scroll_display, *scrolling_display;

void setup(void) {
    no_scroll_display = cowpi_add_display_module(
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
    scrolling_display = cowpi_add_display_module(
            (cowpi_display_module_t) {
                    .display_module = SEVEN_SEGMENT,
                    .width = 8,
                    .height = 1,
                    .words_per_minute = 30
            },
            (cowpi_display_module_protocol_t) {
                    .protocol = SPI,
                    .data_pin = MOSI,
                    .clock_pin = SCK,
                    .select_pin = SS
            }
    );
    fprintf(scrolling_display, "Hello World!\n");
    // normally, using two file streams on the same display module can have
    // undesired effects, but in this simple example, we should be okay if
    // we wait until the scolling text is gone
    delay(7000);
}

void loop(void) {
    // On AVR architectures, you can use `fprintf_P` with `PSTR` to put the
    // format string in flash memory, if you want to
#ifdef __AVR__
    fprintf_P(no_scroll_display, PSTR("Hello\n"));
#else
    fprintf(no_scroll_display, "Hello\n");
#endif //__AVR__
    delay(750);
    fprintf(no_scroll_display, "%8s\n", "World!");
    delay(750);
}
