#ifndef LCD_4_BIT_DISPLAY_H
#define LCD_4_BIT_DISPLAY_H

#include <stdint.h>

/* LCD DATA PORT */
#define DDR_LCD DDRC
#define PORT_LCD PORTC

/* CONTROL PORT */
#define DDR_CONTROL DDRL
#define PORT_CONTROL PORTL

/* CONTROL PINS */
#define REGISTER_SELECT 0
#define READ_WRITE 1
#define ENABLE 2

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
void PrintIntAt(int value, uint8_t row, uint8_t col);
void PrintDoubleAt(double value, uint8_t row, uint8_t col);

/* CUSTOM CHAR */
void CreateCustomChar(uint8_t *data, uint8_t position);
void ShowCustomChar(uint8_t position, uint8_t row, uint8_t col);

#endif