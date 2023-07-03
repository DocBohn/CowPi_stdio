# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

<!--

## [major.minor.patch] - yyyy-mm-dd

-->

<!--
- `Added` for new features.
- `Changed` for changes in existing functionality.
- `Deprecated` for soon-to-be removed features.
- `Removed` for now removed features.
- `Fixed` for any bug fixes.
- `Security` in case of vulnerabilities.
-->

<!--
## [TODO]
- Add `include/` directory? (more conformal to PlatformIO)
- Code for controlling SSD1306-based display modules
- File stream for OLED matrix (SSD1306)
- File stream for arbitrary Arduino Stream
- File stream for arbitrary UART
- Fix printf on Nano 33 BLE
- Fix hardware I2C on simulator (works fine on actual hardware)
- Code for chained MAX7219 modules
- tweak configuration code
- port to Raspberry Pi Pico SDK framework
- Buffer timer for ATmega4809, SAMD21
- Rename stdio setup
-->

## [0.5.0] - 2023-07-03

### Added

- File streams that require a timed buffer
  - File stream for scrolling text on 7 segment display module (MAX7219)
  - File stream for 8x8 LED matrix (MAX7219)
  - File stream for Morse Code
- Documentation

## [0.4.4] - 2023-06-22

### Added

- File streams to send text to display modules using `fprintf`
  - 8 digit, 7 segment display module (MAX7219)
  - 16 column, 2 row character display module (HD44780)
  - 16 column, 4 row character display module (HD44780)

### Changed

- Migrated code for controlling MAX7219- and HD44780-based display modules migrated from CowPi library to CowPi_stdio library
- `cowpi_lcd1602_xxx()` functions from CowPi library are now `cowpi_hd44780_xxx()` in CowPi_stdio library
  - More consistent with `cowpi_max7219_xxx()` and (the upcoming) `cowpi_ssd1306_xxx()`

## [0.4.3] - 2023-06-04

### Added

- ARM (SAMD, MBED) `printf`/`scanf` code

## [0.4.2] - 2023-06-01

### Added

- Extracted CowPi_stdio as a separate library

### Changed

- Migrated AVR `printf`/`scanf` code from CowPi library to CowPi_stdio library

## [0.4.0] - 2023-01-26

### Added

- Part of CowPi library
    - LCD1602 default dialect for SPI

## [0.3.0] - 2022-08-01

### Added

- Part of CowPi library
    - Setup code to enable `printf`/`scanf` for AVR microcontrollers
    - 7-segment and dot-matrix fonts
    - Framework to control HD44780-based display module

## [0.2.1] - 2022-04-26

### Added

- Part of CowPi library
    - Default implementation to send data to MAX7219-based display module

## [0.2.0] - 2022-04-01

### Added

- Part of CowPi library
    - Setup code to configure MAX7219