#include "prototype&header.h"

//lcd command function
void LCD_command(uint8_t command)
{
    GPIO_PORTA_DATA_R = 0;   /* RS = 0, R/W = 0 */
    GPIO_PORTB_DATA_R = (command & 0xff);
    GPIO_PORTA_DATA_R = EN ; 
    delay_us(1);   			     
    GPIO_PORTA_DATA_R = 0;
    if (command < 4)
        delay_ms(2);         /* command 1 and 2 needs up to 1.64ms */
    else
        delay_us(40);        /* all other commands 40 us */
}

/*------------------------------------------------------------------------------------------------------------------*/
//lcd character function
void LCD_char(uint8_t data)
{
    GPIO_PORTA_DATA_R = RS ;        /* RS = 1, R/W = 0 */
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTA_DATA_R = EN | RS ;   /* pulse E */
    delay_us(1);
    GPIO_PORTA_DATA_R = 0;
    delay_us(40);
}
/*------------------------------------------------------------------------------------------------------------------*/
//lcd string function*/
void LCD_string(char *s){
	  int i;
	  for(i=0;s[i]!=0;i++){
		    LCD_char(s[i]);
		    delay_ms(2);
	}
}
/*------------------------------------------------------------------------------------------------------------------*/
//lcd initialization  sequence
void LCD_init(void){
    uint32_t dummy ;
    SYSCTL_RCGCGPIO_R |=0x01;       /* enable port A */
    SYSCTL_RCGCGPIO_R |= 0x02;      /* enable port B */
    dummy = SYSCTL_RCGCGPIO_R;      /* wait for  clk */
    GPIO_PORTB_DIR_R |= 0xFF;       /* make portB all output */
	  GPIO_PORTA_DIR_R |= 0xE0;       /* PA5, PA6, PA7 output */
    GPIO_PORTB_DEN_R |= 0xFF;       /* enable port b all digital */
  	GPIO_PORTA_DEN_R |= 0xE0;       /* enable used pins in port a digital */
    delay_ms(20);            
    LCD_command(0x30);              /*Function Set: 8 – bit Mode, 1 Line, 5×7 Dots*/
    delay_ms(5);
    LCD_command(0x30);      	
    delay_us(100);
    LCD_command(0x30);
    LCD_command(0x38);              /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x01);              /* clear screen */
    LCD_command(0x02);              /* return cursor to home */
    LCD_command(0x0F);              /* turn on display, cursor blinking */

}
/*-----------------------------------------End lcd------------------------------------------------------------------*/