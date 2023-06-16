#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

#include <stdbool.h>
#include <stdint.h>
#include "../lib/CowPi_stdio/src/communication/i2c.h"

cowpi_display_module_protocol_t pins;
FILE *display;
const uint8_t backslash = 0x01;   // ROM Code A00 has a Yen symbol instead of '\\'

void fill_display(void);

void setup(void) {
    cowpi_stdio_setup(9600);
    pinMode(SDA, INPUT);
    pinMode(SCL, INPUT);

    int8_t address = cowpi_discover_i2c_address(SDA, SCL);
    if (address == 0) {
        printf("no devices detected\n");
        while (1) {}
    } else if (address == -1) {
        printf("multiple devices detected\n");
        while (1) {}
    } else {
        printf("device detected at %#04x\n", address);
    }
    if (!(0x20 <= address && address <= 0x27) && !(0x38 <= address && address <= 0x3F)) {
        printf("This might not be an HD44780 LCD character display.\n");
    }

    pins = cowpi_configure_i2c(SDA, SCL, address);

    display = cowpi_add_display_module(
            (cowpi_display_module_t) {
                    .display_module = LCD_CHARACTER
            },
            pins
    );
    if (!display) {
        printf("received NULL file pointer\n");
        while (1) {}
    }

    uint8_t backslash_matrix[8];
    cowpi_font_ascii_to_5wide_dotmatrix(backslash_matrix, '\\');
    cowpi_hd44780_create_character(&pins, backslash, backslash_matrix);

    cowpi_hd44780_clear_display(&pins);
    // On AVR architectures, you can use `fprintf_P` with `PSTR` to put the
    // format string in flash memory, if you want to
    // !!! Notice how much RAM the text in this example uses !!!
#ifdef __AVR__
    fprintf_P(display, PSTR("Hello, World!\n"));
#else
    fprintf(display, "Hello, World!\n");
#endif //__AVR__
    delay(1000);
}

void loop(void) {
    fill_display();
    fprintf(display, "Most characters\n");
    fprintf(display, "overwrite others\n");
    fill_display();
    printf("Horizontal tab (\\t, 0x09) advances 1 space without overwriting the character.\n");
    fprintf(display, "Advance\tcursor\n");
    fprintf(display, "\t\twith\t%ct\n", (char) backslash);
    fill_display();
    printf("Form feed, or new page, (\\f, 0x0C) places the cursor in the top row and performs a carriage return.\n");
    fprintf(display, "return home\n");
    fprintf(display, "  with %cf\f", (char) backslash);
    delay(1500);
    fprintf(display, "like this\n");
    fill_display();
    printf("Vertical tab (\\v, 0xB) advances to the next row without clearing any characters, and performs a carriage return\n");
    fprintf(display, "Go to next row\v");
    fprintf(display, "  with %cv\v", (char) backslash);
    fill_display();
    printf("Line feed, or new line, (\\n, 0xA) clears the remaining characters, advances to the next row, and performs a carriage return\n");
    fprintf(display, "Clear row & go\n");
    fprintf(display, "to next row: %cn\n", (char) backslash);
    fill_display();
    printf("Carriage return (\\r, 0x0D) places the cursor at the left posistion of the current row.\n");
    fprintf(display, "Go to row start\n");
    fprintf(display, "  with %cr  \r", (char) backslash);
    delay(1500);
    fprintf(display, "like this\n");
    fill_display();
    fprintf(display, "A too-long string advances row.\n");
    fill_display();
    fprintf(display, "\f\v\vAdvancing past\nthe bottom\n");
    delay(1500);
    fprintf(display, "goes to the top.\n");
}

void fill_display(void) {
    delay(2000);
    fprintf(display, "\f----------------\n");
    fprintf(display, "----------------\n");
    fprintf(display, "----------------\n");
    fprintf(display, "----------------\f");
    delay(1000);
}
