#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD_4_BIT_Display.h"

static void PulseEnable(){
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);

    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(50);
}

static void SendNibble(uint8_t nibble){

    /* clear data pins PL4–PL7 */
    LCD_PORT &= 0x0F;

    /* place nibble on PL4–PL7 */
    LCD_PORT |= (nibble << 4);

    PulseEnable();
}

static void SendByte(uint8_t value){
    SendNibble(value >> 4);   // high nibble
    SendNibble(value & 0x0F); // low nibble
}

void InitPins(void){
    LCD_DDR |= (1<<LCD_RS) |
               (1<<LCD_RW) |
               (1<<LCD_EN) |
               (1<<LCD_BL) |
               (1<<LCD_D4) |
               (1<<LCD_D5) |
               (1<<LCD_D6) |
               (1<<LCD_D7);

    /* enable backlight */
    LCD_PORT |= (1<<LCD_BL);
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

    WriteCommand(0x28);
    WriteCommand(0x0C);
    WriteCommand(0x06);
    WriteCommand(0x01);

    _delay_ms(2);
}

void WriteCommand(uint8_t value){

    LCD_PORT &= ~(1 << LCD_RS);
    LCD_PORT &= ~(1 << LCD_RW);

    SendByte(value);
}

void WriteData(uint8_t value){

    LCD_PORT |= (1 << LCD_RS);
    LCD_PORT &= ~(1 << LCD_RW);

    SendByte(value);
}

void GoToPosition(uint8_t row, uint8_t col){

    uint8_t address;

    if(row == 1){
        address = col;
    }else{
        address = 0x40 + col;
    }

    WriteCommand(0x80 + address);
}

void PrintChar(uint8_t character){
    WriteData(character);
}

void PrintString(char *string){

    while(*string){
        PrintChar(*string++);
    }
}

void PrintStringAt(char *string, uint8_t row, uint8_t col){

    GoToPosition(row, col);
    PrintString(string);
}

void PrintIntAt(int value, uint8_t row, uint8_t col){

    char buffer[12];

    itoa(value, buffer, 10);

    PrintStringAt(buffer, row, col);
}

void PrintDoubleAt(double value, uint8_t row, uint8_t col){

    char buffer[16];

    dtostrf(value, 6, 3, buffer);

    PrintStringAt(buffer, row, col);
}

void CreateCustomChar(uint8_t *data, uint8_t position){

    uint8_t i;

    if(position > 7){
        position = 7;
    }

    WriteCommand(0x40 + (position * 8));

    for(i = 0; i < 8; i++){
        WriteData(data[i]);
    }
}

void ShowCustomChar(uint8_t position, uint8_t row, uint8_t col){

    if(position > 7){
        position = 0;
    }

    GoToPosition(row, col);
    PrintChar(position);
}