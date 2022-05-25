#include "prototype&header.h"
bool Is_Open_Door = false; //if false the door is closed if ture the door is open

int main()
{
unsigned char key; // used to get pressed key
keypad_init();     //keypad initialization part
LCD_init();        //lcd initialization part
while(1){            //lcd main page 
	LCD_command(clear_display);  //clear display
	LCD_string("Enter a choice");
	LCD_command(CURSOR_ON_2ND_LINE);
	LCD_string("to begin cooking");
	delay_ms(250);
	key = keypad_scan();	// scan for pressed key by user
	switch(key){
		case 'A':
	        	popcorn();
		break;
					
		case 'B':
			beef();
		break;
									
       		case 'C':
			chicken();
		break;
					
		case 'D':
	        	custom_cooking();
		break;
									
		default:
			LCD_command(clear_display);
			LCD_string("enter Characters");
			LCD_command(CURSOR_ON_2ND_LINE);
			LCD_string("from A, B, C, D");
		        delay_sec(2);
		break;
				}
			}
		}

