# Yada

## ASCII Codes

| Display Module                |      `\a`       |                                     `\b`                                     |        `\t`         |                `\n`                |                 `\v`                 |           `\f`            |             `\r`             |                             0x1B (gcc `\e`)                             |                 0x7F                 |
|:------------------------------|:---------------:|:----------------------------------------------------------------------------:|:-------------------:|:----------------------------------:|:------------------------------------:|:-------------------------:|:----------------------------:|:-----------------------------------------------------------------------:|:------------------------------------:|
| ASCII                         |      bell       |                                  backspace                                   |   horizontal tab    |             line feed              |             vertical tab             |         form feed         |       carriage return        |                                 escape                                  |                delete                |
| nominal CowPi_stdio behavior  |       n/a       | shifts cursor left; next character is inclusive-ORed with existing character | shifts cursor right | clears remaining line, then `\v\r` | places cursor in next row, then `\r` | places cursor in top left | places cursor in left column |                        sends next byte literally                        | `\b`, then clears existing character |
| 7-segment display (no scroll) |   prints `7`    |                                      ✅                                       |          ✅          |                 ✅                  |                  ✅                   |            ✅`             |              ✅               | next byte specifies a segment pattern; *see MAX7219 datasheet, Table 6* |                  ✅                   |
| LCD character display         | prints CGRAM[7] |                               prints CGRAM[8]                                |          ✅          |                 ✅                  |                  ✅                   |             ✅             |              ✅               |                            prints CGROM[27]                             |          prints CGROM[127]           |

## Special Functions

|        Display Module        |                  `cowpi_clear_display`                  |                         `cowpi_sleep_display`                         |         `cowpi_wake_display`          |
|:----------------------------:|:-------------------------------------------------------:|:---------------------------------------------------------------------:|:-------------------------------------:|
| nominal CowPi_stdio behavior | Removes all displayed characters and performs form feed | Places display in low-power state while remembering displayed content | Restores display from low-power state |
|      7-segment display       |                            ✅                            |                   Places MAX7219 in "shutdown" mode                   | Takes MAX7219 out of "shutdown" mode  |
|    LCD character display     |                            ✅                            |                          Disables backlight                           |           Enables backlight           |
