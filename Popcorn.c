#include "prototype&header.h"


void popcorn(){
				unsigned int i;		//used for for loop
				int* ad;		//used to get the address of j
				int j = 0;
				ad = &j;
				
				SYSCTL_RCGCGPIO_R |=0x30;		//intialization of portF and portE delay
				while ((SYSCTL_PRGPIO_R&0x30) ==  0){};
				GPIO_PORTF_LOCK_R= 0x4C4F434B;		//initialization of portF switchs
				GPIO_PORTF_CR_R |= 0x11;
				GPIO_PORTF_AFSEL_R &= ~0x11;
				GPIO_PORTF_PCTL_R &= ~0x11;
				GPIO_PORTF_AMSEL_R &= ~0x000F000F;
				GPIO_PORTF_DIR_R &= ~0x11;
				GPIO_PORTF_DEN_R |= 0x11;
				GPIO_PORTF_PUR_R |= 0x11;
				
				
				GPIO_PORTF_LOCK_R = 0x4c4f434b;		//initialization of potF LEDs
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
				
				
				LCD_command(clear_display);	//clear lcd before writting to avoid overlaping
				LCD_string("Popcorn");	// write on lcd
				delay_ms(250);
				
				while(1){
					if(((GPIO_PORTF_DATA_R & 0x01) == 0) && ((GPIO_PORTE_DATA_R & 0x20) != 0)){		//check for the start botton and door
						goto rt;
					}
				}
				
rt:			LCD_command(clear_display);		//running time screen
				LCD_string("remaining Time:");
				LCD_command(CURSOR_ON_2ND_LINE);
				LCD_string("01:00");		//show 01:00 for one second
				GPIO_PORTF_DATA_R |= 0x0E;
				delay_SW1_SW3_ms(1000, ad);		//check for switch 1 and the door statues
				if(j == 1){
					j = 0;
					LCD_command(CURSOR_POSITION_SH_RIGHT);
					LCD_command(CURSOR_POSITION_SH_RIGHT);
					LCD_string("(Paused)");		//paused screen
					delay_ms(350);
					while(1){
						GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//blink the leds when paused
						delay_SW1_SW2_ms(500,ad);		//check for switch 1 and 2 statues
						if(j == 1){		//in case of pressing stop
							j = 0;
							goto end;
						}
						if(j == 2){		//in case of pressing start
							j = 0;
							goto rt;
						}
					}
				}
						
				if(j == 3){		//in case the door was opened
					j = 0;
					while(1){
						GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//blink the leds when the door is opened
						delay_SW3_ms(500,ad);
						if(j == 3){
							j = 0;
							goto rt;
						}
					}
				}
				
				for(i=59; i>0; i--){		//for loop to start counting down
					char x [2];		//initiate arrays to print
cont:			sprintf(x, "%d", i); 	//turn integer into char so i can print it on lcd
					LCD_command(clear_display);
					LCD_string("remaining Time:");		//running time screen
					LCD_command(CURSOR_ON_2ND_LINE);
					LCD_string("00:");		//print 00: to keep the clock style 00:00
					if(i < 10){
						LCD_string("0");		//when its less than print 0 to keep the clock style 00:00
					}
					LCD_string(x);
					GPIO_PORTF_DATA_R |= 0x0E;
					delay_SW1_SW3_ms(1000, ad);		//check for switch 1 and door statues
					
					if(j == 1){		//in case of pressing pause
						j = 0;
						LCD_command(CURSOR_POSITION_SH_RIGHT);
						LCD_command(CURSOR_POSITION_SH_RIGHT);
						LCD_string("(Paused)");
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
								goto cont;
							}
						}
					}
					
					if(j == 3){		//in case the door was opened
						j = 0;
						while(1){
							GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;		//blink the leds when the door is opened
							delay_SW3_ms(500,ad);
							if(j == 3){
								j = 0;
								goto cont;
							}
						}
					}
				}
				
				GPIO_PORTF_DATA_R &= ~0x0E;		//turn off the leds after finishing
				LCD_command(clear_display);
				LCD_string("your cooking");		//end of cooking screen
				LCD_command(CURSOR_ON_2ND_LINE);
				LCD_string("is ready");
				LEDs_flash_3times();		//blink the leds 3 times
end:   	GPIO_PORTF_DATA_R &= ~0x0E;		//turn off the leds when stoping
}


