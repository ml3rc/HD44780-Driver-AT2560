#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"

uint8_t currentRow = 1;
uint8_t currentCol = 0;

/* Internal helpers */
static void PulseEnable(){
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(50);
}

static void SendNibble(uint8_t nibble){
	LCD_PORT &= 0x0F;          // clear upper data pins
	LCD_PORT |= (nibble << 4); // place nibble on PL4–PL7
	PulseEnable();
}

static void SendByte(uint8_t value){
	SendNibble(value >> 4);
	SendNibble(value & 0x0F);
}

/* Public functions */
void InitPins(void){
	LCD_DDR |= (1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN)|
	(1<<LCD_BL)|(1<<LCD_D4)|(1<<LCD_D5)|
	(1<<LCD_D6)|(1<<LCD_D7);
	LCD_PORT |= (1<<LCD_BL);  // backlight on
}

void InitDisplay(void){
	_delay_ms(30);
	SendNibble(0x03);
	_delay_ms(10);
	SendNibble(0x03);
	_delay_us(200);
	SendNibble(0x03);
	_delay_us(200);
	SendNibble(0x02);

	WriteCommand(0x28); // 4-bit, 2 lines
	WriteCommand(0x0C); // display on, cursor off
	WriteCommand(0x06); // entry mode increment
	WriteCommand(0x01); // clear display
	_delay_ms(2);
}

void WriteCommand(uint8_t value){
	LCD_PORT &= ~(1<<LCD_RS | 1<<LCD_RW);
	SendByte(value);
}

void WriteData(uint8_t value){
	LCD_PORT |= (1<<LCD_RS);
	LCD_PORT &= ~(1<<LCD_RW);
	SendByte(value);
}

void GoToPosition(uint8_t row, uint8_t col){
	currentCol = col;
	currentRow = row;
	uint8_t addr = (row == 1) ? col : 0x40 + col;
	WriteCommand(0x80 + addr);
}

void PrintChar(uint8_t c) {
	switch(c) {
		case '\n': {
			// newline -> move to next line
			currentRow = (currentRow == 1) ? 2 : 1;
			currentCol = 0;
			GoToPosition(currentRow, currentCol);
			break;
		}

		case '\r': {
			// carriage return -> move to start of current line
			currentCol = 0;
			GoToPosition(currentRow, currentCol);
			break;
		}

		case '\t': {
			// tab -> 4 spaces
			uint8_t spaces = 4;
			while(spaces--) {
				WriteData(' ');
				currentCol++;
				if(currentCol >= 16) {
					currentCol = 0;
					currentRow = (currentRow == 1) ? 2 : 1;
					GoToPosition(currentRow, currentCol);
				}
			}
			break;
		}

		case '\b': {
			// backspace -> move one column back and clear
			if(currentCol > 0) {
				currentCol--;
				GoToPosition(currentRow, currentCol);
				WriteData(' ');
				GoToPosition(currentRow, currentCol);
			}
			break;
		}

		case '\f': {
			// form feed -> clear display
			ClearDisplay();
			currentRow = 1;
			currentCol = 0;
			break;
		}

		case '\v': {
			// vertical tab -> move to next row, keep column
			currentRow = (currentRow == 1) ? 2 : 1;
			GoToPosition(currentRow, currentCol);
			break;
		}

		default: {
			// normal printable character
			WriteData(c);
			currentCol++;
			if(currentCol >= 16) {
				currentCol = 0;
				currentRow = (currentRow == 1) ? 2 : 1;
				GoToPosition(currentRow, currentCol);
			}
			break;
		}
	}
}

void PrintString(char *s){
	while(*s) PrintChar(*s++);
}

void PrintStringAt(char *s, uint8_t row, uint8_t col){
	GoToPosition(row, col);
	PrintString(s);
}

/* Simple operations */
void ClearDisplay(void){
	WriteCommand(0x01);
	_delay_ms(2);
}

void ShiftRight(void){
	WriteCommand(0x1C);
}

void ShiftLeft(void){
	WriteCommand(0x18);
}

/* Custom characters */
void CreateCustomChar(uint8_t *data, uint8_t pos){
	if(pos > 7) pos = 7;
	WriteCommand(0x40 + pos*8);
	for(uint8_t i=0; i<8; i++) WriteData(data[i]);
}

void ShowCustomChar(uint8_t pos, uint8_t row, uint8_t col){
	if(pos > 7) pos = 0;
	GoToPosition(row, col);
	PrintChar(pos);
}