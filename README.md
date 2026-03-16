# HD44780 LCD 4-Bit Library for AVR

A **lightweight C library** for controlling **HD44780-compatible character LCD displays** in **4-bit mode** using AVR microcontrollers. This library was designed for the **PICado Mega** but works with most AVR MCUs.

The library aims for:

* Small code size
* Clear and simple structure
* Easy integration into embedded projects
* Consistent naming: variables use `thisCase`, functions use `ThisCase`

---

## Repository Contents

```
HD44780.c
HD44780.h
```

---

## Origin

This library is **derived from the work of Nawi**:

[Original project](https://github.com/nawicool/LCD-4BIT-Display/tree/master)

It simplifies the original library while preserving essential functionality, making it easier to use in small projects.

---

## Key Changes from Original

* Reduced code size and complexity
* Simplified internal LCD write functions
* Consolidated string printing and command handling
* Easier-to-read naming conventions
* Updated CGRAM/custom character handling

---

## Features

* HD44780-compatible LCD support
* 4-bit communication mode
* Cursor positioning and movement
* Print characters and strings
* Support for integers and floats (optional)
* Custom character creation in CGRAM
* Handles special characters like `\n`, `\r`, `\t`, `\b`, `\f`, and `\v`

---

## Hardware Connections Example

| LCD Pin | AVR Port |
| ------- | -------- |
| RS      | PL0      |
| RW      | PL1      |
| EN      | PL2      |
| BL      | PL3      |
| D4      | PL4      |
| D5      | PL5      |
| D6      | PL6      |
| D7      | PL7      |

> Pins can be redefined in `HD44780.h` if needed.

---

## Basic Usage

```c
#include <avr/io.h>
#include "HD44780.h"

int main(void) {
    InitPins();
    InitDisplay();

    PrintStringAt("Hello", 1, 0);
    PrintStringAt("World", 2, 0);

    while(1) { }
}
```

---

## Handling Special Characters

This library handles commonly used delimiters automatically when printing strings:

* `\n` → Move to the start of the next row
* `\r` → Move to the start of the current row
* `\t` → Inserts 4 spaces (tab)
* `\b` → Backspace (erase previous character)
* `\f` → Clears display
* `\v` → Moves to the next row, same column

Example:

```c
PrintStringAt("Hello\tWorld!\nNew Line", 1, 0);
```

---

## Creating Custom Characters

HD44780 LCDs support **8 custom characters** in CGRAM:

```c
uint8_t smiley[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00
};

CreateCustomChar(smiley, 0);
ShowCustomChar(0, 1, 5); // Display custom char at row 1, column 5
```

---

## Supported Displays

Works with most HD44780-based LCDs, including:

* 16x2 LCD
* 20x4 LCD
* Other standard character LCDs compatible with HD44780

---

## Requirements

* AVR microcontroller
* avr-gcc toolchain
* `<avr/io.h>` and `<util/delay.h>`

---

## License

This library is licensed under the **GNU General Public License v2 or later**, consistent with the original project by Nawi.

[Original repository](https://github.com/nawicool/LCD-4BIT-Display/tree/master)