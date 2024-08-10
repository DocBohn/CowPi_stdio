# SSD1306 Display Functions

Until I implement a `FILE` stream the SSD1306 display module in the CowPi_stdio library, you can place these files in your project.

- `src/display.h` and `src/display.cpp`
  - Place these files in your project's `src/` directory with your application code
- `lib/pgmspace/pgmspace.h`
  - If you're using the Adafruit_SSD1306 library and are *not* targeting an AVR platform, then place the `pgmspace` directory in your project's `lib/` directory
    - There is a bug in the Adafruit_SSD1306 library in that it attempts to import the Arduino core's `pgmspace.h` file from the wrong directory for some platforms
  - This file is unneeded if you're using the OneBitDisplay library, but it's harmless (unless you're targeting an AVR platform)
  - If you're targeting an AVR platform, do *not* place this file in your project.

These files need either the Adafruit_SSD1306 library
```ini
lib_deps =
  adafruit/Adafruit SSD1306@^2.5.11
```
or the OneBitDisplay library.
```ini
lib_deps = 
  bitbank2/OneBitDisplay@^2.3.1
```

## Minimal functions

- `initialize_display()` configures the display module
- `clear_display()` blanks the display
- `draw_logo()` displays the CowPi logo on the display module
- `display_string()` places a string in the buffer at a specified row
  - If the string ends with `\n` then the function will flush the buffer to the display
- `refresh_display()` flushes the buffer to the display

## Diagnostic functions

These functions are not needed but might be useful now and again.
They output to both the Serial Monitor and to the display module.

- `print_versions()` prints:
  - the version numbers for gcc, CowPi, and CowPi_stdio
  - whether the Arduino core is backed by avr-libc, MBED OS, or the RPi Pico SDK (arduino-pico)
  - whether the display is driven by the OneBitDisplay library or the Adafruit_SSD1306 library
- `record_build_timestamp()` and `print_build_timestamps()` help you make sure that you've uploaded the most-current version of your code
  - If each of your `.c` or `.cpp` files calls `record_build_timestamp(__FILE__, __DATE__, __TIME__);` once, then `print_build_timestamps()` will print the date/time when each file was compiled
  - If you just edited a file a minute ago but the most recent timestamp is several minutes ago, then the running program does not have your most recent edits.