#include "prototype&header.h"

void chicken(){
	unsigned char key; // used to get pressed key
	unsigned int time=0; //used to define time for cooking
	int i;
	int u;
	unsigned int time_min = 0;
	unsigned int time_sec = 0;
	int* ad;
	int j = 0;
	ad = &j;
	
		SYSCTL_RCGCGPIO_R |=0x30;
	while ((SYSCTL_PRGPIO_R&0x30) ==  0){};
	GPIO_PORTF_LOCK_R= 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x11;
	GPIO_PORTF_AFSEL_R &= ~0x11;
	GPIO_PORTF_PCTL_R &= ~0x11;
	GPIO_PORTF_AMSEL_R &= ~0x000F000F;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x11;
	GPIO_PORTF_PUR_R |= 0x11;
	
	
	GPIO_PORTF_LOCK_R = 0x4c4f434b;
	GPIO_PORTF_AMSEL_R &= ~0x0E;
	GPIO_PORTF_AFSEL_R &= ~0x0E;
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_PCTL_R &= ~0x0000fff0;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_CR_R |= 0x0E;
	GPIO_PORTF_DATA_R &= ~0x0E;
	
	
	GPIO_PORTE_CR_R |= 0x20;
	GPIO_PORTE_AMSEL_R &= ~0x20;
	GPIO_PORTE_PCTL_R &= ~0x00F00000;
	GPIO_PORTE_AFSEL_R &= ~0x20;
	GPIO_PORTE_DIR_R &= ~0x20;
	GPIO_PORTE_DEN_R |= 0x20;
	GPIO_PORTE_DATA_R |= 0x20;
	GPIO_PORTE_PUR_R |= 0x20;
	
re:
	LCD_command(clear_display);	//clear lcd before writting to avoid overlaping
	LCD_string("Chicken weight?");	// write on lcd
	delay_ms(250);
	key = keypad_scan();	// scan for pressed key
	LCD_command(clear_display);
	LCD_char(key);
	delay_ms(500);
	
	while(key == 'A'| key == 'B'| key == 'C'| key == 'D'| key == '*'| key == '#' | key == '0'){ // for loob to avoid chars
		LCD_command(clear_display);
		LCD_string("please enter one");
		LCD_command(CURSOR_ON_2ND_LINE);
		LCD_string("digit from 1-9");
		delay_sec(2);
		goto re;
	}
	time = key - '0';
	time = time * 12; // calc time
	time_min = time/60;
	time_sec = time%60;
	
		while(1){
		
		if(((GPIO_PORTF_DATA_R & 0x01) == 0) && ((GPIO_PORTE_DATA_R & 0x20) != 0)){
			goto rt;
		}
	}
	
rt:
	
	for(i=time_sec; i>=0; i--){
		char x [3];
		char y [3];
cont1:
		sprintf(x, "%d", i); //turn integer into char so i can print it on lcd
		sprintf(y, "%d", time_min);
		LCD_command(clear_display);
		LCD_string("remaining Time:");
		LCD_command(CURSOR_ON_2ND_LINE);
		if(time_min < 10){
			LCD_char('0');
		}
		LCD_string(y);
		LCD_char(':');
		if(i < 10){
			LCD_char('0');
		}
		LCD_string(x);
		GPIO_PORTF_DATA_R |= 0x0E;
		delay_SW1_SW3_ms(1000, ad);
		
		if(j == 1){
			j = 0;
			LCD_command(CURSOR_POSITION_SH_RIGHT);
			LCD_command(CURSOR_POSITION_SH_RIGHT);
			LCD_string("(Paused)");
			delay_ms(350);
			while(1){
				GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;
				delay_SW1_SW2_ms(500,ad);
				if(j == 1){
					j = 0;
					goto end;
				}
				if(j == 2){
					j = 0;
					goto cont1;
				}
			}
		}
				if(j == 3){
					j = 0;
					while(1){
						GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;
						delay_SW3_ms(500,ad);
						if(j == 3){
							j = 0;
							goto cont1;
						}
					}
				}
	}
		
			for(i=time_min - 1; i>=0; i--){
				char x [3];
				char y [3];
				sprintf(y, "%d", i);
			for(u = 59; u >= 0; u--){
cont2:
				LCD_command(clear_display);
				LCD_string("remaining Time:");
				LCD_command(CURSOR_ON_2ND_LINE);
				sprintf(x, "%d", u);
				if(i < 10){
					LCD_char('0');
				}
				LCD_string(y);
				LCD_char(':');
				if(u < 10){
					LCD_char('0');
				}
				LCD_string(x);
				GPIO_PORTF_DATA_R |= 0x0E;
				delay_SW1_SW3_ms(1000, ad);
				
				if(j == 1){
					j = 0;
					LCD_command(CURSOR_POSITION_SH_RIGHT);
					LCD_command(CURSOR_POSITION_SH_RIGHT);
					LCD_string("(Paused)");
					delay_ms(350);
					while(1){
						GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;
						delay_SW1_SW2_ms(500,ad);
						if(j == 1){
							j = 0;
							goto end;
						}
						if(j == 2){
							j = 0;
							goto cont2;
						}
					}
				}
				
				if(j == 3){
					j = 0;
					while(1){
						GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;
						delay_SW3_ms(500,ad);
						if(j == 3){
							j = 0;
							goto cont2;
						}
					}
				}
			}
		}
	
	GPIO_PORTF_DATA_R &= ~0x0E;
	LCD_command(clear_display);		
	LCD_string("your cooking");
	LCD_command(CURSOR_ON_2ND_LINE);
	LCD_string("is ready");
	LEDs_flash_3times();
end:   GPIO_PORTF_DATA_R &= ~0x0E;
}


