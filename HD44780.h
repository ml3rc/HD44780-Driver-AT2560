#ifndef LCD_4_BIT_DISPLAY_H
#define LCD_4_BIT_DISPLAY_H

#include <stdint.h>

/* LCD PORT CONFIGURATION */
#define LCD_PORT PORTL
#define LCD_DDR  DDRL

/* CONTROL PINS */
#define LCD_RS 0   /* PL0 */
#define LCD_RW 1   /* PL1 */
#define LCD_EN 2   /* PL2 */

/* BACKLIGHT */
#define LCD_BL 3   /* PL3 */

/* DATA PINS (4-bit mode) */
#define LCD_D4 4   /* PL4 */
#define LCD_D5 5   /* PL5 */
#define LCD_D6 6   /* PL6 */
#define LCD_D7 7   /* PL7 */

/* INIT */
void InitPins(void);
void InitDisplay(void);

/* LOW LEVEL */
void WriteCommand(uint8_t value);
void WriteData(uint8_t value);

/* CURSOR */
void GoToPosition(uint8_t row, uint8_t col);

/* TEXT */
void PrintChar(uint8_t character);
void PrintString(char *string);
void PrintStringAt(char *string, uint8_t row, uint8_t col);

/* DISPLAY OPERATIONS */
void ClearDisplay(void);
void ShiftLeft(void);
void ShiftRight(void);

/* CUSTOM CHARACTERS */
void CreateCustomChar(uint8_t *data, uint8_t position);
void ShowCustomChar(uint8_t position, uint8_t row, uint8_t col);

#endif