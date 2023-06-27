# CowPi_stdio Library

[![GitHub release](https://img.shields.io/github/release/DocBohn/CowPi_stdio)](https://github.com/DocBohn/CowPi_stdio/releases)
[![GitHub](https://img.shields.io/github/license/DocBohn/CowPi_stdio)](https://github.com/DocBohn/CowPi_stdio/blob/main/LICENSE)

[//]: # ([![arduino-library-badge]&#40;https://www.ardu-badge.com/badge/CowPi_stdio.svg?&#41;]&#40;https://www.ardu-badge.com/CowPi_stdio&#41;)

[//]: # (![Build with PlatformIO]&#40;https://img.shields.io/badge/build%20with-PlatformIO-orange?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzkzLjgxIDAgNjEuNjY2IDEzLjMxNCAzNy40OSAzNy40OSAxMy4zMTQgNjEuNjY2IDAgOTMuODEgMCAxMjhjMCAzNC4xOSAxMy4zMTQgNjYuMzM0IDM3LjQ5IDkwLjUxQzYxLjY2NiAyNDIuNjg2IDkzLjgxIDI1NiAxMjggMjU2YzM0LjE5IDAgNjYuMzM0LTEzLjMxNCA5MC41MS0zNy40OUMyNDIuNjg2IDE5NC4zMzQgMjU2IDE2Mi4xOSAyNTYgMTI4YzAtMzQuMTktMTMuMzE0LTY2LjMzNC0zNy40OS05MC41MUMxOTQuMzM0IDEzLjMxNCAxNjIuMTkgMCAxMjggMCIgZmlsbD0iI0ZGN0YwMCIvPjxwYXRoIGQ9Ik0yNDkuMzg2IDEyOGMwIDY3LjA0LTU0LjM0NyAxMjEuMzg2LTEyMS4zODYgMTIxLjM4NkM2MC45NiAyNDkuMzg2IDYuNjEzIDE5NS4wNCA2LjYxMyAxMjggNi42MTMgNjAuOTYgNjAuOTYgNi42MTQgMTI4IDYuNjE0YzY3LjA0IDAgMTIxLjM4NiA1NC4zNDYgMTIxLjM4NiAxMjEuMzg2IiBmaWxsPSIjRkZGIi8+PHBhdGggZD0iTTE2MC44NjkgNzQuMDYybDUuMTQ1LTE4LjUzN2M1LjI2NC0uNDcgOS4zOTItNC44ODYgOS4zOTItMTAuMjczIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzJzLTEwLjMyIDQuNjItMTAuMzIgMTAuMzJjMCAzLjc1NSAyLjAxMyA3LjAzIDUuMDEgOC44MzdsLTUuMDUgMTguMTk1Yy0xNC40MzctMy42Ny0yNi42MjUtMy4zOS0yNi42MjUtMy4zOWwtMi4yNTggMS4wMXYxNDAuODcybDIuMjU4Ljc1M2MxMy42MTQgMCA3My4xNzctNDEuMTMzIDczLjMyMy04NS4yNyAwLTMxLjYyNC0yMS4wMjMtNDUuODI1LTQwLjU1NS01Mi4xOTd6TTE0Ni41MyAxNjQuOGMtMTEuNjE3LTE4LjU1Ny02LjcwNi02MS43NTEgMjMuNjQzLTY3LjkyNSA4LjMyLTEuMzMzIDE4LjUwOSA0LjEzNCAyMS41MSAxNi4yNzkgNy41ODIgMjUuNzY2LTM3LjAxNSA2MS44NDUtNDUuMTUzIDUxLjY0NnptMTguMjE2LTM5Ljc1MmE5LjM5OSA5LjM5OSAwIDAgMC05LjM5OSA5LjM5OSA5LjM5OSA5LjM5OSAwIDAgMCA5LjQgOS4zOTkgOS4zOTkgOS4zOTkgMCAwIDAgOS4zOTgtOS40IDkuMzk5IDkuMzk5IDAgMCAwLTkuMzk5LTkuMzk4em0yLjgxIDguNjcyYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDkgMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OXoiIGZpbGw9IiNFNTcyMDAiLz48cGF0aCBkPSJNMTAxLjM3MSA3Mi43MDlsLTUuMDIzLTE4LjkwMWMyLjg3NC0xLjgzMiA0Ljc4Ni01LjA0IDQuNzg2LTguNzAxIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzItNS42OTkgMC0xMC4zMTkgNC42Mi0xMC4zMTkgMTAuMzIgMCA1LjY4MiA0LjU5MiAxMC4yODkgMTAuMjY3IDEwLjMxN0w5NS44IDc0LjM3OGMtMTkuNjA5IDYuNTEtNDAuODg1IDIwLjc0Mi00MC44ODUgNTEuODguNDM2IDQ1LjAxIDU5LjU3MiA4NS4yNjcgNzMuMTg2IDg1LjI2N1Y2OC44OTJzLTEyLjI1Mi0uMDYyLTI2LjcyOSAzLjgxN3ptMTAuMzk1IDkyLjA5Yy04LjEzOCAxMC4yLTUyLjczNS0yNS44OC00NS4xNTQtNTEuNjQ1IDMuMDAyLTEyLjE0NSAxMy4xOS0xNy42MTIgMjEuNTExLTE2LjI4IDMwLjM1IDYuMTc1IDM1LjI2IDQ5LjM2OSAyMy42NDMgNjcuOTI2em0tMTguODItMzkuNDZhOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTkgOS4zOTggOS4zOTkgOS4zOTkgMCAwIDAgOS40IDkuNCA5LjM5OSA5LjM5OSAwIDAgMCA5LjM5OC05LjQgOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTktOS4zOTl6bS0yLjgxIDguNjcxYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDggMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OHoiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=&#41;)

![See also CowPi](https://img.shields.io/badge/see_also-CowPi-crimson?logo=data:image/png;base64,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X0tI0vXTqQ83tV4cOSJJh5b/vZBXZTV8tnFZR2hJJ6nIW0t3AuXl0+8NPuvrawK62oteqPz0wqPNDubQ5wU7qhxaQX1d8a96nwag8bokyRnqnj7RJSlcv+knRdfSKUk7qb4kSTJp8nR6Ev0AjIXm8nWVd19uAfz7PljD6HjZKmDiBLX3AGBhto5fPBzG1Zb6JHOT4z+0F6V7Nqxf6QLcjwEjsYYAcP4PGjzzukjaA/7R4eKqMW0tHFZyfzpPhpfYlpW0F/NgThcApiAWjCfaAjx4YwkWyTsWOhQbocEEexBfHYtRsk8Bhb4tYcm+kZEOTCwGOed390gK17IumhfFnuLeSrv2xcz4ZDhqe9a6Uos6DF+rWAmMXaGulFz5wERkd3tF5urYt/Let8EzeTK4KrCA9Gl5BXA2znozD/m+5Q0LylbPHflqJoMb54nId9xfDJyhsD5/+C/tsAh9EQGY6T0P25Kz88jJCzwApEYpq85DUu4q6NmyfRymX2nZD2X+mdx15vBNbz2QmKCklGv9dg5xLBds3Xe2D859uWsPGAXzwzt0jMAKIJsh/udvL++K5Jqcff+qJGfgsjTVn5SUendmrp/RFtielZR+AmNF5bKjjiQk6eujt+7dQGfO6W9sqO+QJH2zzut/8pQkyRCQ7qhpXvgE4Ez/M2VzXjqBUewG4EqopLoAAEMAie5EY02xCWg2fDr5uP/ffgsjt9i//xh1FboNO2V719S5+C8IpKem0yrwlt7JbewvvQDRbTfTM8MAAACWZVhJZk1NACoAAAAIAAUBEgADAAAAAQABAAABGgAFAAAAAQAAAEoBGwAFAAAAAQAAAFIBKAADAAAAAQACAACHaQAEAAAAAQAAAFoAAAAAAAAAkAAAAAEAAACQAAAAAQADkoYABwAAABIAAACEoAIABAAAAAEAAANgoAMABAAAAAEAAAGqAAAAAEFTQ0lJAAAAU2NyZWVuc2hvdBGuL+cAAAAldEVYdGRhdGU6Y3JlYXRlADIwMjMtMDYtMjZUMjE6MzM6MzIrMDA6MDB4qO9iAAAAJXRFWHRkYXRlOm1vZGlmeQAyMDIzLTA2LTI2VDIxOjMwOjU1KzAwOjAw4Qrb1AAAACh0RVh0ZGF0ZTp0aW1lc3RhbXAAMjAyMy0wNi0yNlQyMTo0MjoyNyswMDowMAaLJ4UAAAASdEVYdGV4aWY6RXhpZk9mZnNldAA5MFmM3psAAAAYdEVYdGV4aWY6UGl4ZWxYRGltZW5zaW9uADg2NBjUGH0AAAAYdEVYdGV4aWY6UGl4ZWxZRGltZW5zaW9uADQyNgajpEcAAAAWdEVYdGV4aWY6VXNlckNvbW1lbnQAQVNDSUm041reAAAAKHRFWHRpY2M6Y29weXJpZ2h0AENvcHlyaWdodCBBcHBsZSBJbmMuLCAyMDIy5LS/nAAAABd0RVh0aWNjOmRlc2NyaXB0aW9uAERpc3BsYXkXG5W4AAAAEnRFWHR0aWZmOk9yaWVudGF0aW9uADG3q/w7AAAAF3RFWHR4bXA6UGl4ZWxYRGltZW5zaW9uADg5MIIujSYAAAAXdEVYdHhtcDpQaXhlbFlEaW1lbnNpb24ANDI2HKzpygAAABp0RVh0eG1wOlVzZXJDb21tZW50AFNjcmVlbnNob3TT4LJ8AAAAAElFTkSuQmCC)

[//]: # (![See also CowPi]&#40;https://img.shields.io/badge/see_also-CowPi-crimson?logo=data:image/png;base64,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&#41;)

[//]: # (![See also CowPi]&#40;https://img.shields.io/badge/see_also-CowPi-crimson?logo=data:image/png;base64,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&#41;)

[//]: # ([![GitHub issues]&#40;https://img.shields.io/github/issues/DocBohn/CowPi_stdio&#41;]&#40;http://github.com/DocBohn/CowPi_stdio/issues&#41;)


## What the CowPi_stdio library has to offer

This library brings `printf` and `scanf`, familiar to any C programmer, to Arduino boards with AVR microcontrollers.

Specifically, the library defines the `stdout` and `stdin` file streams, which are then used by `printf` and `scanf`.

## What the CowPi_stdio library will have to offer

Our plans for the v0.5 release include:

- File streams for assorted display modules to use with `fprintf`

Our plans for the v0.6 release include:

- File streams for display modules in the Raspberry Pi Pico SDK framework
- File streams for UART devices that are not (necessarily) connected to USB
- File streams for additional display modules

## Examples

The examples are all `.ino` files as expected by the Arduino IDE.
(Maybe) You can use them in PlatformIO by creating a `main.cpp` file that consists only of

```cpp
#include "../lib/CowPi_stdio/examples/example_name/example_name.ino"
```

(where `example_name` is replaced with the actual example's name)

### printf_and_scanf

Demonstrates the use of `printf` (including the nonstandard `printf_P` and `PSTR` functions provided by avr-libc), as
well as `scanf`.

### printf_limitations

Demonstrates the limitations of floating point conversions and 64-bit integer conversions.
(See the note about [limitations](#Limitations), below.)

### scan_i2c

Demonstrates the use of `cowpi_discover_i2c_address`

### max7219_seven_segment

Demonstrates using `fprintf` with an 8 digit, 7 segment display module.

### hd44780_blinky

Used to test whether an LCD character display is connected properly by blinking the display module's backlight while
displaying "Hello, world!" so that the user an adjust the contrast trimpot.
Just for fun, this example also demonstrates the use of custom characters, by having a 👻 (which might or might not be
inspired by Pac-Man's [Blinky](https://pacman.fandom.com/wiki/Blinky)) move back and forth.

### hd44780_lcd_character

Demonstrates using `fprintf` with a 16x2 (or 20x4) LCD character display module.

## The tradeoffs

### Advantage of using `printf`

- Being able to print using a format string with conversion specifiers is *much* more convenient than using the
  Arduino `Serial.print` and `Serial.println` functions.
  Even without specifying alignment and padding, as soon as you combine constant text with a variable, `printf` becomes
  easier to use than a chain of `Serial.print`/`println` calls.
  (But, of course, you have all the conversion specifier goodness, including alignment and padding.
  Well, *almost* all -- see the note below about [limitations](#Limitations).)

### Disadvantage of using `printf`

- Using `printf` *will* increase the size of your executable by about 1.2KB over simply using `Serial.print`
  and `Serial.println`, about the same as if you were to combine `snprintf` with `Serial.println`.

  For example, on an Arduino Nano,
  ```cpp
  void setup(void) {
    Serial.begin(9600);
    int a = 3, b = 7;
    Serial.print(a);
    Serial.print(" + ");
    Serial.print(b);
    Serial.print(" = ");
    Serial.println(a + b);
  }

  void loop(void) {
  }
  ```
  uses 1814 bytes of Flash memory and 196 bytes of SRAM, whereas,
  ```cpp
  #include <CowPi_stdio.h>

  void setup(void) {
    cowpi_stdio_setup(9600);
    int a = 3, b = 7;
    printf("%d + %d = %d\n", a, b, a + b);
  }

  void loop(void) {
  }
  ```
  uses 3054 bytes of Flash memory and 218 bytes of SRAM.

### Neither advantage nor disadvantage

- Even without using the CowPi_stdio library, you can create formatted output by using `sprintf` (or, better
  yet, `snprintf`).
  This, however, still brings the code for format conversions into the program:
  ```cpp
  void setup(void) {
    Serial.begin(9600);
    int a = 3, b = 7;
    char string[11] = { 0 };
    snprintf(string, 11, "%d + %d = %d", a, b, a + b);
    Serial.println(string);
  }

  void loop(void) {
  }
  ```
  uses 3066 bytes of Flash memory and 200 bytes of SRAM.
- Conventional wisdom is that format conversions are very slow.
  While it is true that using `printf` is slower than not printing to a terminal, it is *not* true that using `printf`
  is slower than chaining `Serial.print`/`println` calls.
  The `Serial.print` and `Serial.println` statements in the first snippet require 276µs (±4µs) to execute, and
  the `printf` statement in the second snippet requires 212µs (±4µs) to execute.

## Limitations

The only limitations are inherited from the avr-libc (for AVR) and the newlib (for ARM) libraries.
The one you will most likely notice is floating point conversions, which can be overcome.
There are other limitations that cannot be.

### Floating point conversions

Like most microcontroller environments, the default implementation does not support floating point conversions (except
for Raspberry Pi Pico).
Instead, the output will be `?` on AVR architectures.
On ARM (SAMD) architectures, the output is an unprintable character.

Another implementation is available that will support floating point conversions.

- For AVR architectures, the richer implementation is available through a compiler (linker) option:
  ```
  -Wl,-u,vfprintf -lprintf_flt -lm
  ```
  If you're using the Arduino IDE, you'll need to set up a `platform.local.txt` file;
  if you're using PlatformIO, you can add the build flags to your `platform.ini` file.
  ***Note**: the richer implementation will add about 1.4KB to your executable.*

- We're still determining how to get the richer implementation for ARM (SAMD).

<!--
    Try `-Wl,-u,_printf_float` (and also `-Wl,-u,_scanf_float`)
    -or-
    in the source code
    `asm (".global _floatf_float");`
    `asm (".global _scanf_float");`
-->

### Other limitations

- The specified width and precision can be at most 255 on AVR architectures.
  This is unlikely to be a practical limitation.
- `long long` conversions (*i.e.*, 64-bit integers) are not supported.
  The `%lld` conversion specifier will abort the output on AVR architectures.
  On ARM architectures, `ld` is output.
  This also is unlikely to be a practical limitation.
- Variable width or precision fields is not supported on AVR architectures.
  Using `*` to specify the width or precision will abort the output.
  Lines 105-108 and 119-122 of *hd44780_blinky* have code that must work around this limitation.

## Compatability

| MCU                        | `printf`/`scanf` | SPI bitbang | SPI hardware | I2C bitbang | I2C hardware | Notes                                                                                                                             |
|:---------------------------|:----------------:|:-----------:|:------------:|:-----------:|:------------:|:----------------------------------------------------------------------------------------------------------------------------------|
| ATmega328P                 |        ✅         |      ✅      |      ✅       |      ✅      |      ✅       | I2C code works fine on actual hardware but not in simulator (bitbang I2C works for both)                                          |
| ATmega2560                 |        ✅         |      ✅      |      ✅       |      ✅      |      ✅       | I2C code works fine on actual hardware but not in simulator (bitbang I2C works for both)                                          |
| ATmega4809                 |        ✅         |      ⁇      |      ❌       |      ⁇      |      ❌       |                                                                                                                                   |
| nRF52840                   |        ❌         |      ⁇      |      ❌       |      ⁇      |      ❌       | Locks up USB -- problem with waiting for Serial? <!-- https://forum.arduino.cc/t/nano-33-ble-sense-serial-workaround/884962/7 --> |
| RP2040 (Arduino framework) |        ✅         |      ✅      |      ❌       |      ✅      |      ❌       | Still need to resolve floating point conversions; SPI and I2C implemented as bit-bang only                                        |
| SAM D21                    |        ✅         |      ⁇      |      ❌       |      ⁇      |      ❌       | Still need to resolve floating point conversions                                                                                  |

[//]: # (| RA4M1                      |        ⁇         |      ⁇      |      ❌       |      ⁇      |      ❌       |                                                                                                                                   |)

(It looks like *some* of the ICSP pins on the Arduino Mega 2560 aren't connected to the SPI pins (50-53) even though
schematic indicates they are -- this just might be my particular board)

| Display Module                                                    | AVR | megaAVR | MBED | SAMD |
|:------------------------------------------------------------------|:---:|:-------:|:----:|:----:|
| 8-digit, 7-segment display (MAX7219, 5V)                          |  ✅  |    ⁇    |  ✅   |  ⁇   |
| 8-digit, 7-segment scrolling display (MAX7219, 5V)                |  ❌  |    ❌    |  ❌   |  ❌   |
| 8x8 LED matrix scrolling display (MAX7219, 5V)                    |  ❌  |    ❌    |  ❌   |  ❌   |
| 16x2 LCD character display (HD44780, 5V; some devices claim 3.3V) |  ✅  |    ⁇    |  ✅   |  ⁇   |
| 20x4 LCD character display (HD44780, 5V; some devices claim 3.3V) |  ✅  |    ⁇    |  ✅   |  ⁇   |
| 128x64 OLED matrix display (SSD1306, 3.3V or 5V)                  |  ❌  |    ❌    |  ❌   |  ❌   |
| 128x32 OLED matrix display (SSD1306, 3.3V or 5V)                  |  ❌  |    ❌    |  ❌   |  ❌   |
| Morse Code LED (no serial adapter necessary)                      |  ✅  |    ❌    |  ❌   |  ❌   |

[//]: # (| 8x12 LED matrix scrolling display &#40;Uno R4 Wifi&#41;                   |  ❌  |    ❌    |  ❌   |  ❌   |)

(MBED tested on Raspberry Pi Pico but not on Arduino Nano 33 BLE)

### Tested on...

- AVR
    - AVR
        - Atmel ATmega328P
            - [x] Arduino Uno R3
            - [x] Arduino Nano
        - Atmel ATmega2560:
            - [x] Arduino Mega 2560
    - megaAVR
        - Atmel ATmega4809
            - [ ] Arduino Uno Wifi Rev 2
            - [x] Arduino Nano Every
- ARM
    - Mbed OS
        - Nordic nRF52840
            - [x] Arduino Nano 33 BLE (see notes, above)
        - Raspberry Pi RP2040
            - [ ] Arduino Nano RP2040 Connect
            - [x] Raspberry Pi Pico (Arduino platform)
    - SAMD
        - Atmel SAM D21:
            - [x] Arduino Nano 33 IoT
            - [ ] Arduino Zero

[//]: # (  - RENESAS)

[//]: # (    - [ ] Renesas RA4M1: Arduino Uno R4)

## About the name

Some of the code in the CowPi_stdio library was once part of the [CowPi](https://github.com/DocBohn/CowPi/) library,
which was designed to work with Cow Pi development boards.
The code in the CowPi_stdio library will work in projects that do not use a Cow Pi development board, but we preserve
the "CowPi" part of the name as a nod to its origins, and also to distinguish it from the `stdio` portion of libc.
The "stdio" part of the name is because it makes available to AVR architectures two of the most-commonly used functions
from `stdio.h` and makes it possible for coders to use stdio functions to work with display modules for both AVR and ARM
architectures.

### Why *Cow Pi*?

Because it's punny.

### No, I mean, *-Pi* is typically used as a suffix for circuits that use a Raspberry Pi instead of an Arduino.

Typically, yes, but *Cowduino* isn't very punny, is it?
Besides, it will (soon) also work with the Raspberry Pi Pico.

## An abbreviated pre-history

Some of the code in the CowPi_stdio library was once part of the [CowPi](https://github.com/DocBohn/CowPi/) library,
which was designed to work with Cow Pi development boards, designed for class assignments at the hardware/software
interface.
Version 0.3 of the CowPi library saw many improvements, including being able to use `printf()` and `scanf()` with a
serial terminal and abstractions for controlling MAX7219- and HH44780-based display modules.
Plans for v0.5 included abstractions for SSD1306-based display modules and to further abstract the display modules by
creating file streams for them that can be used with `fprintf()`.
As we were making initial forays into what this display code would look like, we realized that the code that controls
the displays depends on the displays but not on any of the other hardware on the Cow Pi development board, and we
realized that it might be useful for projects that don't use the Cow Pi development board.

And so we separated the display code out from the rest of the CowPi library.
