# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

<!--

## [major.minor.patch] - yyyy-mm-dd

-->

## [Unreleased]

- Code for controlling MAX7219- and HD44780-based display modules migrated from CowPi library to CowPi_stdio library
- Code for controlling SSD1306-based display modules
- File streams to send text to display modules using `fprintf`
- `printf`/`scanf` for ARM architectures

<!--
- `Added` for new features.
- `Changed` for changes in existing functionality.
- `Deprecated` for soon-to-be removed features.
- `Removed` for now removed features.
- `Fixed` for any bug fixes.
- `Security` in case of vulnerabilities.
-->

## [0.4.2] - 2023-06-01

### Added

- Extracted CowPi_stdio as a separate library

### Changed

- Migrated `printf`/`scanf` code from CowPi library to CowPi_stdio library

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

## [0.2.0] - 2-22-04-01

### Added

- Part of CowPi library
  - Setup code to configure MAX7219