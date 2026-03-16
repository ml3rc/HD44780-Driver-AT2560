# HD44780 LCD 4-Bit Library (AVR)

A small C library for controlling **HD44780 compatible character LCD displays** in **4-bit mode** using AVR microcontrollers.

The goal of this library is to provide a **simple and compact driver** that can easily be used in small embedded projects.

This implementation focuses on:

* small code size
* simple and readable structure
* clear naming conventions
* compatibility with common AVR microcontrollers

The source files in this repository are:

```
HD44780.c
HD44780.h
```

---

# Origin

This library is **derived from the project below**:

https://github.com/nawicool/LCD-4BIT-Display/tree/master

The original work was written by **Nawi** and released under the **GNU General Public License (GPL v2 or later)**.

This version modifies the original implementation to simplify the structure and reduce code size while keeping the same basic functionality.

---

# Changes From The Original

Compared to the original library, the following changes were made:

* reduced overall code size
* simplified command handling
* removed several redundant wrapper functions
* simplified internal LCD write functions
* simplified CGRAM handling
* simplified string printing
* updated naming conventions

Naming conventions used in this version:

* variables use `thisCase`
* functions use `ThisCase`

These changes were made to improve readability and make the library easier to integrate into embedded projects.

---

# Features

* HD44780 compatible LCD support
* 4-bit communication mode
* cursor positioning
* printing characters and strings
* printing integers
* printing floating point numbers
* custom character support (CGRAM)

---

# Hardware Connections (Example)

Example pin mapping used in the library:

| LCD Pin | AVR Pin |
| ------- | ------- |
| D4      | PC0     |
| D5      | PC1     |
| D6      | PC2     |
| D7      | PC3     |
| RS      | PL0     |
| RW      | PL1     |
| EN      | PL2     |

These pins can be changed in **HD44780.h**.

---

# Basic Usage

Example program:

```c
#include <avr/io.h>
#include "HD44780.h"

int main(void){

    InitPins();
    InitDisplay();

    PrintStringAt("Hello", 1, 0);
    PrintStringAt("World", 2, 0);

    while(1){
    }
}
```

---

# Creating Custom Characters

HD44780 displays allow **up to 8 custom characters** stored in CGRAM.

Example:

```c
uint8_t smiley[8] = {
0x00,
0x0A,
0x00,
0x00,
0x11,
0x0E,
0x00,
0x00
};

CreateCustomChar(smiley, 0);
ShowCustomChar(0, 1, 5);
```

---

# Supported Displays

The library works with most **HD44780 compatible character LCD modules**, including:

* 16x2 LCD
* 20x4 LCD
* other HD44780 based displays

---

# Requirements

* AVR microcontroller
* avr-gcc
* `<avr/io.h>`
* `<util/delay.h>`

---

# License

This project remains licensed under the **GNU General Public License v2 or later**, in accordance with the original project.

Original project repository:

https://github.com/nawicool/LCD-4BIT-Display/tree/master
