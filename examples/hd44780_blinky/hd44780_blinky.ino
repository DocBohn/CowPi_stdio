#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

#include <stdbool.h>
#include <stdint.h>

#ifdef __MBED__
#define SDA PIN_WIRE_SDA
#define SCL PIN_WIRE_SCL
#endif

cowpi_display_module_protocol_t pins;
FILE *display;

void setup(void) {
    cowpi_stdio_setup(9600);


    // **********
    // CHOOSE SERIAL-TO-PARALLEL MAPPING (typically can omit adapter mapping if using COWPI_DEFAULT)
    enum adapter_mappings adapter_mapping = COWPI_DEFAULT;
    // enum adapter_mappings adapter_mapping = ADAFRUIT;
    // **********


    // **********
    // CHOOSE I2C OR SPI
    /*
    pins = cowpi_configure_spi(MOSI, SCK, SS, adapter_mapping);
    */
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
    pins = cowpi_configure_i2c(SDA, SCL, address, adapter_mapping);
    // **********


    display = cowpi_add_display_module(
            (cowpi_display_module_t) {
                    .display_module = LCD_CHARACTER,
                //    .width = 20,
                //    .height = 4
            },
            pins
    );
    if (!display) {
        printf("received NULL file pointer\n");
        while (1) {}
    } else {
        printf("You should see the backlight blinking.\n");
        printf("Adjust the contrast until you can see the \"Hello, world!\" message.\n");
        fprintf(display, "Hello, world!\n");
    }

    // uint8_t blinky[][8] = {
    //         {0x0E, 0x1F, 0x1D, 0x1F, 0x1F, 0x1F, 0x15, 0x15},
    //         {0x0E, 0x1F, 0x1D, 0x1F, 0x1F, 0x1F, 0x0A, 0x0A},
    //         {0x0E, 0x1F, 0x17, 0x1F, 0x1F, 0x1F, 0x15, 0x15},
    //         {0x0E, 0x1F, 0x17, 0x1F, 0x1F, 0x1F, 0x0A, 0x0A},
    // };
    uint8_t blinky[][8] = {
            {0x0E, 0x1F, 0x1D, 0x1F, 0x1F, 0x1F, 0x1F, 0x15},
            {0x0E, 0x1F, 0x1D, 0x1F, 0x1F, 0x1F, 0x1F, 0x0A},
            {0x0E, 0x1F, 0x17, 0x1F, 0x1F, 0x1F, 0x1F, 0x15},
            {0x0E, 0x1F, 0x17, 0x1F, 0x1F, 0x1F, 0x1F, 0x0A},
    };
    cowpi_hd44780_create_character(&pins, 1, blinky[0]);
    cowpi_hd44780_create_character(&pins, 2, blinky[1]);
    cowpi_hd44780_create_character(&pins, 3, blinky[2]);
    cowpi_hd44780_create_character(&pins, 4, blinky[3]);
}

void loop(void) {
    unsigned long time = millis();
    cowpi_hd44780_set_backlight(&pins, time & 0x400);
    static enum {
        WAITING_LEFT, MOVING_LEFT, WAITING_RIGHT, MOVING_RIGHT
    } mode = WAITING_RIGHT;
    static int8_t column = 0;
    static int8_t blinky_frame = 1;
    static bool alternate = false;
    if (alternate ^ !(time & 0x100)) {
        alternate = !alternate;
        blinky_frame += alternate ? 1 : -1;
        switch (mode) {
            case WAITING_LEFT:
                fprintf(display, "%13c\r", blinky_frame);
                if (column == 20) {
                    mode = MOVING_LEFT;
                    column = 9;
                } else {
                    column++;
                }
                break;
            case WAITING_RIGHT:
                fprintf(display, "%4c \r", blinky_frame);
                if (column == 20) {
                    mode = MOVING_RIGHT;
                    column = 0;
                } else {
                    column++;
                }
                break;
            case MOVING_LEFT:
                // gotta do it this way since AVR doesn't do variable-width conversions
                for (int i = 0; i < column; i++) {
                    fprintf(display, " ");
                }
                fprintf(display, "%4c \r", blinky_frame);
                if (column == 0) {
                    mode = WAITING_RIGHT;
                    column = 0;
                    blinky_frame = 1;
                    alternate = false;
                } else {
                    column--;
                }
                break;
            case MOVING_RIGHT:
                for (int i = 0; i < column; i++) {
                    fprintf(display, " ");
                }
                fprintf(display, "%4c\r", blinky_frame);
                if (column == 9) {
                    mode = WAITING_LEFT;
                    column = 0;
                    blinky_frame = 3;
                    alternate = false;
                } else {
                    column++;
                }
                break;
            default:
                printf("Surprising mode: %d\n", mode);
        }
    }
}
