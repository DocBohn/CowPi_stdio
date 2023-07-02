# CowPi_stdio Library

[![GitHub release](https://img.shields.io/github/release/DocBohn/CowPi_stdio)](https://github.com/DocBohn/CowPi_stdio/releases)
[![GitHub license](https://img.shields.io/github/license/DocBohn/CowPi_stdio)](https://github.com/DocBohn/CowPi_stdio/blob/main/LICENSE)

[//]: # ([![arduino library]&#40;https://www.ardu-badge.com/badge/CowPi_stdio.svg?&#41;]&#40;https://www.ardu-badge.com/CowPi_stdio&#41;)

[//]: # (![platformIO library]&#40;https://img.shields.io/badge/Library_Registry-CowPi_stdio-orange?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzkzLjgxIDAgNjEuNjY2IDEzLjMxNCAzNy40OSAzNy40OSAxMy4zMTQgNjEuNjY2IDAgOTMuODEgMCAxMjhjMCAzNC4xOSAxMy4zMTQgNjYuMzM0IDM3LjQ5IDkwLjUxQzYxLjY2NiAyNDIuNjg2IDkzLjgxIDI1NiAxMjggMjU2YzM0LjE5IDAgNjYuMzM0LTEzLjMxNCA5MC41MS0zNy40OUMyNDIuNjg2IDE5NC4zMzQgMjU2IDE2Mi4xOSAyNTYgMTI4YzAtMzQuMTktMTMuMzE0LTY2LjMzNC0zNy40OS05MC41MUMxOTQuMzM0IDEzLjMxNCAxNjIuMTkgMCAxMjggMCIgZmlsbD0iI0ZGN0YwMCIvPjxwYXRoIGQ9Ik0yNDkuMzg2IDEyOGMwIDY3LjA0LTU0LjM0NyAxMjEuMzg2LTEyMS4zODYgMTIxLjM4NkM2MC45NiAyNDkuMzg2IDYuNjEzIDE5NS4wNCA2LjYxMyAxMjggNi42MTMgNjAuOTYgNjAuOTYgNi42MTQgMTI4IDYuNjE0YzY3LjA0IDAgMTIxLjM4NiA1NC4zNDYgMTIxLjM4NiAxMjEuMzg2IiBmaWxsPSIjRkZGIi8+PHBhdGggZD0iTTE2MC44NjkgNzQuMDYybDUuMTQ1LTE4LjUzN2M1LjI2NC0uNDcgOS4zOTItNC44ODYgOS4zOTItMTAuMjczIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzJzLTEwLjMyIDQuNjItMTAuMzIgMTAuMzJjMCAzLjc1NSAyLjAxMyA3LjAzIDUuMDEgOC44MzdsLTUuMDUgMTguMTk1Yy0xNC40MzctMy42Ny0yNi42MjUtMy4zOS0yNi42MjUtMy4zOWwtMi4yNTggMS4wMXYxNDAuODcybDIuMjU4Ljc1M2MxMy42MTQgMCA3My4xNzctNDEuMTMzIDczLjMyMy04NS4yNyAwLTMxLjYyNC0yMS4wMjMtNDUuODI1LTQwLjU1NS01Mi4xOTd6TTE0Ni41MyAxNjQuOGMtMTEuNjE3LTE4LjU1Ny02LjcwNi02MS43NTEgMjMuNjQzLTY3LjkyNSA4LjMyLTEuMzMzIDE4LjUwOSA0LjEzNCAyMS41MSAxNi4yNzkgNy41ODIgMjUuNzY2LTM3LjAxNSA2MS44NDUtNDUuMTUzIDUxLjY0NnptMTguMjE2LTM5Ljc1MmE5LjM5OSA5LjM5OSAwIDAgMC05LjM5OSA5LjM5OSA5LjM5OSA5LjM5OSAwIDAgMCA5LjQgOS4zOTkgOS4zOTkgOS4zOTkgMCAwIDAgOS4zOTgtOS40IDkuMzk5IDkuMzk5IDAgMCAwLTkuMzk5LTkuMzk4em0yLjgxIDguNjcyYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDkgMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OXoiIGZpbGw9IiNFNTcyMDAiLz48cGF0aCBkPSJNMTAxLjM3MSA3Mi43MDlsLTUuMDIzLTE4LjkwMWMyLjg3NC0xLjgzMiA0Ljc4Ni01LjA0IDQuNzg2LTguNzAxIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzItNS42OTkgMC0xMC4zMTkgNC42Mi0xMC4zMTkgMTAuMzIgMCA1LjY4MiA0LjU5MiAxMC4yODkgMTAuMjY3IDEwLjMxN0w5NS44IDc0LjM3OGMtMTkuNjA5IDYuNTEtNDAuODg1IDIwLjc0Mi00MC44ODUgNTEuODguNDM2IDQ1LjAxIDU5LjU3MiA4NS4yNjcgNzMuMTg2IDg1LjI2N1Y2OC44OTJzLTEyLjI1Mi0uMDYyLTI2LjcyOSAzLjgxN3ptMTAuMzk1IDkyLjA5Yy04LjEzOCAxMC4yLTUyLjczNS0yNS44OC00NS4xNTQtNTEuNjQ1IDMuMDAyLTEyLjE0NSAxMy4xOS0xNy42MTIgMjEuNTExLTE2LjI4IDMwLjM1IDYuMTc1IDM1LjI2IDQ5LjM2OSAyMy42NDMgNjcuOTI2em0tMTguODItMzkuNDZhOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTkgOS4zOTggOS4zOTkgOS4zOTkgMCAwIDAgOS40IDkuNCA5LjM5OSA5LjM5OSAwIDAgMCA5LjM5OC05LjQgOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTktOS4zOTl6bS0yLjgxIDguNjcxYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDggMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OHoiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=&#41;)

[![See also CowPi](https://img.shields.io/badge/🐮_𝜋_see_also-CowPi-crimson)](https://github.com/DocBohn/CowPi)

## What the CowPi_stdio library has to offer

This library brings `printf` and `scanf`, familiar to any C programmer, to Arduino boards with AVR microcontrollers.

Specifically, the library defines the `stdout` and `stdin` file streams, which are then used by `printf` and `scanf`.

This library brings `FILE` streams to the Arduino toolchain.
Specifically, the library defines `stdout` and `stdin` file streams to use the USB connection to a host computer.
This brings `printf` and `scanf`, familiar to any C programmer, to Arduino boards.
The library also provides `FILE` streams for assorted display modules, allowing programmers to use `fprintf` to send
text to the display modules

## What the CowPi_stdio library will have to offer

Our plans for upcoming releases include:

- File streams for display modules in the Raspberry Pi Pico SDK framework
- File streams for UART devices that are not (necessarily) connected to USB
- File streams for additional display modules

## Examples

The examples are all `.ino` files as expected by the Arduino IDE.
(Maybe) You can use them in PlatformIO by creating a `main.cpp` file that consists only of

```cpp
#include "../examples/example_name/example_name.ino"
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

| MCU                        | `printf`/`scanf` | SPI bitbang | SPI hardware | I2C bitbang | I2C hardware |   Buffer Timer    | Notes                                                                                                                             |
|:---------------------------|:----------------:|:-----------:|:------------:|:-----------:|:------------:|:-----------------:|:----------------------------------------------------------------------------------------------------------------------------------|
| ATmega328P                 |        ✅         |      ✅      |      ✅       |      ✅      |      ✅       |  uses registers   | I2C code works fine on actual hardware but not in simulator (bitbang I2C works for both)                                          |
| ATmega2560                 |        ✅         |      ✅      |      ✅       |      ✅      |      ✅       |  uses registers   | I2C code works fine on actual hardware but not in simulator (bitbang I2C works for both)                                          |
| ATmega4809                 |        ✅         |      ⁇      |      ❌       |      ⁇      |      ❌       |         ❌         |                                                                                                                                   |
| nRF52840                   |        ❌         |      ⁇      |      ❌       |      ⁇      |      ❌       |         ⁇         | Locks up USB -- problem with waiting for Serial? <!-- https://forum.arduino.cc/t/nano-33-ble-sense-serial-workaround/884962/7 --> |
| RP2040 (Arduino framework) |        ✅         |      ✅      |      ❌       |      ✅      |      ❌       | uses mbed::Ticker | Still need to resolve floating point conversions                                                                                  |
| SAM D21                    |        ✅         |      ⁇      |      ❌       |      ⁇      |      ❌       |         ❌         | Still need to resolve floating point conversions                                                                                  |

[//]: # (| RA4M1                      |        ⁇         |      ⁇      |      ❌       |      ⁇      |      ❌       |         ⁇         |                                                                                                                                   |)

(It looks like *some* of the ICSP pins on the Arduino Mega 2560 aren't connected to the SPI pins (50-53) even though
schematic indicates they are -- this just might be my particular board)

| Display Module                                                      | AVR | megaAVR | MBED | SAMD |
|:--------------------------------------------------------------------|:---:|:-------:|:----:|:----:|
| 8-digit, 7-segment display (MAX7219, 5V)                            |  ✅  |    ⁇    |  ✅   |  ⁇   |
| 8-digit, 7-segment scrolling display (MAX7219, 5V)                  |  ✅  |    ❌    |  ✅   |  ❌   |
| 8x8 LED matrix scrolling display (MAX7219, 5V)                      |  ✅  |    ❌    |  ✅   |  ❌   |
| 16x2 LCD character display (HD44780, 5V; some devices support 3.3V) |  ✅  |    ⁇    |  ✅   |  ⁇   |
| 20x4 LCD character display (HD44780, 5V; some devices support 3.3V) |  ✅  |    ⁇    |  ✅   |  ⁇   |
| 128x64 OLED matrix display (SSD1306, 3.3V or 5V)                    |  ❌  |    ❌    |  ❌   |  ❌   |
| 128x32 OLED matrix display (SSD1306, 3.3V or 5V)                    |  ❌  |    ❌    |  ❌   |  ❌   |
| Morse Code LED (no serial adapter necessary)                        |  ✅  |    ❌    |  ✅   |  ❌   |

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
