//headers
#include "tm4c123.h" // header file of tm4c123gh6pm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h> // import bool datatype and true, flase 



//keypad_funcs.c
void keypad_init(void);
char keypad_scan(void);

//delay_funcs.c
void delay_ms(unsigned int times);
void delay_us(unsigned int times);
void delay_sec(unsigned int times);
/*-----------------------------------------------------------------------------------------------------------*/
//LCD pins defination
#define LCD_DATA GPIO_PORTB_DATA_R
#define LCD_CTRL GPIO_PORTA_DATA_R
#define RS 0x20 /* PORTA BIT5 mask     RS  = Pin A5*/
#define RW 0x40 /* PORTA BIT6 mask     RW  = pin A6 */  
#define EN 0x80 /* PORTA BIT7 mask     E   = Pin A7 */
/*------------------------------------------------------------------------------------------------------------*/
//LCD_defines
#define clear_display     0x01
#define moveCursorLeft    0x08
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80
#define SET_8BIT_DATA_2LINES 0X38
#define CURSOR_ON_2ND_LINE 0XC0
#define CURSOR_ON_HOME 0X02
#define CURSOR_INCREMENTING 0X04
#define CURSOR_DECREMENTING 0X06
#define CURSOR_POSITION_SH_LEFT 0X10
#define CURSOR_POSITION_SH_RIGHT 0X014
#define DISPLAY_SH_LEFT 0X18
#define DISPLAY_SH_RIGHT 0X1C
/*------------------------------------------------------------------------------------------------------------------------*/
/*lcd functions prototype*/
void LCD_command(uint8_t command) ;
void LCD_char(uint8_t data) ;
void LCD_init(void) ;
void LCD_string(char *s);
/*-------------------------------------------------------------------------------------------------------------------------*/
//Beef.c
void beef(void);

//Chicken.c
void chicken(void);

//Popcorn.c
void popcorn(void);

//LEDs_flash
void system_init(void);


void LEDs_flash_3times (void);


void custom_cooking(void);


char scan_with_clear(void);


void delay_SW1_ms(unsigned int times, int* x);


void delay_SW2_ms(unsigned int times, int* x);


void delay_SW3_ms(unsigned int times, int* x);


void delay_SW1_SW2_ms(unsigned int times, int* x);


void delay_SW1_SW3_ms(unsigned int times, int* x);
