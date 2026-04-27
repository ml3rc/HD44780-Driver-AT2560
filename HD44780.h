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
void DISP_InitPins(void);
void DISP_InitDisplay(void);

/* LOW LEVEL */
void DISP_WriteCommand(uint8_t value);
void DISP_WriteData(uint8_t value);

/* CURSOR */
void DISP_GoToPosition(uint8_t row, uint8_t col);

/* TEXT */
void DISP_PrintChar(uint8_t character);
void DISP_PrintString(char *string);
void DISP_PrintStringAt(char *string, uint8_t row, uint8_t col);

/* DISPLAY OPERATIONS */
void DISP_ClearDisplay(void);
void DISP_ShiftLeft(void);
void DISP_ShiftRight(void);

/* CUSTOM CHARACTERS */
void DISP_CreateCustomChar(uint8_t *data, uint8_t position);
void DISP_ShowCustomChar(uint8_t position, uint8_t row, uint8_t col);

#endif