#include "prototype&header.h"

void LEDs_BUZZ_Init(void){		//initiation of leds and GPIO portE 4
	
	SYSCTL_RCGCGPIO_R |= 0x30;                  // Active clock for port f and port e
	while ((SYSCTL_PRGPIO_R & 0x30)==0){}        // waiting for delay
	GPIO_PORTF_LOCK_R = 0x4c4f434b;             // unlock pins for port f
	GPIO_PORTF_AMSEL_R &= ~0x0E;                // disable analog fun for pf1,2,3
	GPIO_PORTF_AFSEL_R &= ~0x0E;                // disable alternate fun for pf1,2,3
	GPIO_PORTF_DEN_R |= 0x0E;                   // enable digital for pf1,2,3
	GPIO_PORTF_PCTL_R &= ~0x0000fff0;           // clear pctl for pf1,2,3 to make it (GPIO)
	GPIO_PORTF_DIR_R |= 0x0E;                   // initialize direction for pf1,2,3
	GPIO_PORTF_CR_R |= 0x0E;                    // enable change
	GPIO_PORTF_DATA_R |= 0x0E;                 // initialize LEDs to make it on
	 
	 
	GPIO_PORTE_CR_R |= 0x10;                    // enable change
	GPIO_PORTE_AMSEL_R &= ~0x10;                // disable analog fun for pe4
	GPIO_PORTE_PCTL_R &= ~0x000F0000;           // clear pctl for pe4 to make it (GPIO)
	GPIO_PORTE_AFSEL_R &= ~0x10;                // disable alternate fun for pe4
	GPIO_PORTE_DIR_R |= 0x10;                   // initialize direction for pe4
	GPIO_PORTE_DEN_R |= 0x10;                   // enable digital for pe4
	GPIO_PORTE_DATA_R &= ~0x10;									//initialize pe4 to give 0 volt at first
}

void LEDs_flash_3times (void){
	int i;
	
	LEDs_BUZZ_Init();
	
	for( i=0 ; i<7 ; i++ ){			//the leds will blink for 3 times 
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ 0x0E;
		GPIO_PORTE_DATA_R |= 0X10;		//output 3.3 volt to the buzzer
		delay_ms(500);
	}
}
