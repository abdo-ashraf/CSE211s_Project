#include "prototype&header.h"

void custom_cooking(void){
				unsigned char key;		//used to read the keypad input
				unsigned char first_digit = '0';		//first number in the clock 00:0x in char form
				unsigned char second_digit = '0';		//second number in the clock 00:x0 in char form
				unsigned char third_digit = '0';		//third number in the clock 0x:00 in char form
				unsigned char forth_digit = '0';		//forth number in the clock x0:00 in char form
				int first = 0;		//first number in the clock 00:0x in integer form
				int second = 0;		//second number in the clock 00:x0 in integer form
				int third = 0;		//third number in the clock 0x:00 in integer form
				int forth = 0;		//forth number in the clock x0:00 in integer form
				unsigned int time_min = 0;		//time in minutes
				unsigned int time_sec = 0;		//time in seconds
				int e;		//used for for loops
				int u;
				int q;
				int* ad;		//used to get the address of j
				int j = 0;
				ad = &j;
				
				SYSCTL_RCGCGPIO_R |=0x30;			//initialization of portF and portE delays
				while ((SYSCTL_PRGPIO_R&0x30) ==  0){};		//initialization of portF switches
				GPIO_PORTF_LOCK_R= 0x4C4F434B;
				GPIO_PORTF_CR_R |= 0x11;
				GPIO_PORTF_AFSEL_R &= ~0x11;
				GPIO_PORTF_PCTL_R &= ~0x11;
				GPIO_PORTF_AMSEL_R &= ~0x000F000F;
				GPIO_PORTF_DIR_R &= ~0x11;
				GPIO_PORTF_DEN_R |= 0x11;
				GPIO_PORTF_PUR_R |= 0x11;
				
				
				GPIO_PORTF_LOCK_R = 0x4c4f434b;		//initialization of portF LEDs
				GPIO_PORTF_AMSEL_R &= ~0x0E;
				GPIO_PORTF_AFSEL_R &= ~0x0E;
				GPIO_PORTF_DEN_R |= 0x0E;
				GPIO_PORTF_PCTL_R &= ~0x0000fff0;
				GPIO_PORTF_DIR_R |= 0x0E;
				GPIO_PORTF_CR_R |= 0x0E;
				GPIO_PORTF_DATA_R &= ~0x0E;
				
				
				GPIO_PORTE_CR_R |= 0x20;		//initialization of portE 5 for the door
				GPIO_PORTE_AMSEL_R &= ~0x20;
				GPIO_PORTE_PCTL_R &= ~0x00F00000;
				GPIO_PORTE_AFSEL_R &= ~0x20;
				GPIO_PORTE_DIR_R &= ~0x20;
				GPIO_PORTE_DEN_R |= 0x20;
				GPIO_PORTE_DATA_R |= 0x20;
				GPIO_PORTE_PUR_R |= 0x20;
				
st:			first_digit = '0';		//resetting all clock values
				second_digit = '0';
				third_digit = '0';
				forth_digit = '0';
				time_min = 0;
				time_sec = 0;
				first = 0;
				second = 0;
				third = 0;
				forth = 0;
				LCD_command(clear_display);
				LCD_string("Cooking time?");		//choice D default screen
				delay_ms(250);
				key = keypad_scan();
					
				if(key == 'A' | key == 'B' | key == 'C' | key == 'D' | key == '#' | key == '*'){		//show error when entering characters
					LCD_command(clear_display);
					LCD_string("Error: no");
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("chararacters");
					delay_sec(2);
					goto st;
				}
				else if(key == '0' | key == '1' | key == '2' | key == '3' | key == '4' | key == '5'| key =='6' | key == '7' | key == '8'| key == '9'){		//enter the first digit
					first_digit = key;
					LCD_command(clear_display);
					LCD_string("00:0");
					LCD_char(first_digit);
					delay_ms(250);
				}
										
nd:			key = scan_with_clear();
				if(key == '0' | key == '1' | key == '2' | key == '3' | key == '4' | key == '5'| key =='6' | key == '7' | key == '8'| key == '9'){		//enter the second digit
					second_digit = first_digit;
					first_digit = key;
					LCD_command(clear_display);
					LCD_string("00:");
					LCD_char(second_digit);
					LCD_char(first_digit);
					delay_ms(250);
				}
				else if(key == 'A' | key == 'B' | key == 'C' | key == 'D' | key == '#' | key == '*'){		//show error when entering characters
					LCD_command(clear_display);
					LCD_string("Error: no");
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("chararacters");
					delay_sec(2);
					LCD_command(clear_display);
					LCD_string("00:0");
					LCD_char(first_digit);
					goto nd;
				}		//additional feature to start or reset from the first digit
				else if(key == 'R'){
					goto st;
				}
				else if(key == 'S'){
					goto start;
				}
							
rd:			key = scan_with_clear();
					
				if(key == 'A' | key == 'B' | key == 'C' | key == 'D' | key == '#' | key == '*'){		//show error when entering characters
					LCD_command(clear_display);
					LCD_string("Error: no");
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("chararacters");
					delay_sec(2);
					LCD_command(clear_display);
					LCD_string("00:");
					LCD_char(second_digit);
					LCD_char(first_digit);
					goto rd;
				}
				else if(key == '0' | key == '1' | key == '2' | key == '3' | key == '4' | key == '5' | key =='6' | key == '7' | key == '8'| key == '9'){		//enter the third digit
					third_digit = second_digit;
					second_digit = first_digit;
					first_digit = key;
					LCD_command(clear_display);
					LCD_string("0");
					LCD_char(third_digit);
					LCD_string(":");
					LCD_char(second_digit);
					LCD_char(first_digit);
					delay_ms(250);
				}		//additional feature to start or reset from the second digit
				else if(key == 'R'){
					goto st;
				}
				else if(key == 'S'){
					goto start;
				}
						
th:			key = scan_with_clear();
				if(key == '0' | key == '1' | key == '2' | key == '3' | key == '4' | key == '5'| key =='6' | key == '7' | key == '8'| key == '9'){		//enter the forth digit
					forth_digit = third_digit;
					third_digit = second_digit;
					second_digit = first_digit;
					first_digit = key;
					LCD_command(clear_display);
					LCD_char(forth_digit);
					LCD_char(third_digit);
					LCD_string(":");
					LCD_char(second_digit);
					LCD_char(first_digit);
					delay_ms(250);
				}
				else if(key == 'A' | key == 'B' | key == 'C' | key == 'D' | key == '#' | key == '*'){		//show error when entering characters
					LCD_command(clear_display);
					LCD_string("Error: no");
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("chararacters");
					delay_sec(2);
					LCD_command(clear_display);
					LCD_string("0");
					LCD_char(third_digit);
					LCD_string(":");
					LCD_char(second_digit);
					LCD_char(first_digit);
					goto th;
				}		//additional feature to start or reset from the third digit
				else if(key == 'R'){
					goto st;
				}
				else if(key == 'S'){
					goto start;
				}

				while(1){
					if(((GPIO_PORTF_DATA_R & 0X11 )==0x10) && ((GPIO_PORTE_DATA_R & 0x20) != 0)){
						goto start;
					}
					if((GPIO_PORTF_DATA_R & 0X11 )==0x01){
						goto st;
					}
				}
						
start:	first = first_digit - '0';		//take the integer of the characters of the keypad
				second = second_digit - '0';
				third = third_digit - '0';
				forth = forth_digit - '0';
				time_min = forth * 10 + third;
				time_sec = second * 10 + first;
						
				if(time_min > 30 || (time_min == 30 & time_sec > 0)){		//in case of entering more than 30 minutes in the minutes part
							
					LCD_command(clear_display);
					LCD_string("Error: maximum");
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("is 30 min");
					delay_sec(2);
					goto st;
				}
						
				if(time_sec >= 60){		//in case of entering more than 59 seconds in the seconds part
							
					LCD_command(clear_display);
					LCD_string("Error: couldn't");
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("exceed 59 sec");
					delay_sec(2);
					goto st;
				}
						
				for(q=time_sec; q>=0; q--){
					char x [3];		//initialize array to print the value
					
cont1:		sprintf(x, "%d", q);
					LCD_command(clear_display);
					LCD_string("remaining Time:");		//running tie screen
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_char(forth_digit);
					LCD_char(third_digit);
					LCD_char(':');
					if(q<10){		//in case of less than 10 print 0 to keep the clock style 00:00
						LCD_char('0');
					}
					LCD_string(x);
					GPIO_PORTF_DATA_R |= 0x0E;
					delay_SW1_SW3_ms(1000, ad);
							
					if(j == 1){		//in case of pressing pause
						j = 0;
						LCD_command(CURSOR_POSITION_SH_RIGHT);
						LCD_command(CURSOR_POSITION_SH_RIGHT);
						LCD_string("(Paused)");		//paused screen
						delay_ms(350);
						while(1){
							GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//blink the leds when paused
							delay_SW1_SW2_ms(500,ad);
							if(j == 1){		//in case of pressing stop
								j = 0;
								goto end;
							}
							if(j == 2){		//in case of pressing start
								j = 0;
								goto cont1;
							}
						}
					}
					
					if(j == 3){		//in case the door was opened
						j = 0;
						while(1){
							GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//the leds blink when  the door is opened
							delay_SW3_ms(500,ad);
							if(j == 3){
								j = 0;
								goto cont1;
							}
						}
					}
				}
						
				for(u = time_min - 1; u>=0; u--){
					char y [3];		//initialize array to print the value
					sprintf(y, "%d", u);
					for(e = 59; e >= 0; e--){
						char z[3];		//initialize array to print the value
							
cont2:			sprintf(z, "%d", e);
						LCD_command(clear_display);
						LCD_string("remaining Time:");		//running time screen
						LCD_command(CURSOR_ON_2ND_LINE);
						if(u<10){		//in case of less than 10 print 0 to keeo the clock style 00:00
							LCD_char('0');
						}
						LCD_string(y);
						LCD_char(':');
						if(e<10){
							LCD_char('0');
						}
						LCD_string(z);
						GPIO_PORTF_DATA_R |= 0x0E;
						delay_SW1_SW3_ms(1000, ad);		//check switch 1 and the door
								
						if(j == 1){		//in case of pressing pause
							j = 0;
							LCD_command(CURSOR_POSITION_SH_RIGHT);
							LCD_command(CURSOR_POSITION_SH_RIGHT);
							LCD_string("(Paused)");		//paused screen
							delay_ms(350);
							while(1){
								GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//blink the leds when paused
								delay_SW1_SW2_ms(500,ad);
								if(j == 1){		//in case of pressing stop
									j = 0;
									goto end;
								}
								if(j == 2){		//in case of pressing start
									j = 0;
									goto cont2;
								}
							}
						}
							
						if(j == 3){		//check for the door statues
							j = 0;
							while(1){
								GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//blink the leds when the door is opened
								delay_SW3_ms(500,ad);
								if(j == 3){
									j = 0;
									goto cont2;
								}
							}
						}
					}
				}
				GPIO_PORTF_DATA_R &= ~0x0E;		//turn off the led when finish cooking
				LCD_command(clear_display);
				LCD_string("your cooking");
				LCD_command(CURSOR_ON_2ND_LINE);
				LCD_string("is ready");
				LEDs_flash_3times();
end:   	GPIO_PORTF_DATA_R &= ~0x0E;		//turn off the leds when stop cooking
}

