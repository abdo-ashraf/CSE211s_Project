#include "prototype&header.h"


const unsigned  char symbolmap[4][4] = {
															 {'1', '2', '3', 'A'},
															 {'4', '5', '6', 'B'},
															 {'7', '8', '9', 'C'},
															 {'*', '0', '#', 'D'}};

//we will use   PE0, PE1, PE2, PE3, PC4, PC5, PC6, PC7 to interface with keypad
void init(){
	// open clk for port E&C
	SYSCTL_RCGCGPIO_R |= 0x14;
	while((SYSCTL_PRGPIO_R & 0x14) == 0){}
		
	// setup port E used pins as input [0-3]
	GPIO_PORTE_CR_R |= 0x0F;
	GPIO_PORTE_AMSEL_R &= ~0x0F;
	GPIO_PORTE_PCTL_R &= ~0x0000FFFF;
	GPIO_PORTE_AFSEL_R &= ~0x0F;
	GPIO_PORTE_DIR_R |= 0x0F;
	GPIO_PORTE_DEN_R |= 0x0F;
	
	//setup port C used pins as output [4-7]
	GPIO_PORTC_CR_R |= 0xF0;
	GPIO_PORTC_AMSEL_R &= ~0xF0;
	GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
	GPIO_PORTC_AFSEL_R &= ~0xF0;
	GPIO_PORTC_DIR_R &= ~0xF0;
	GPIO_PORTC_PUR_R |= 0xF0; // enable PUR for C[4-7]
	GPIO_PORTC_DEN_R |= 0xF0;
	
	SYSCTL_RCGCGPIO_R |=0x20;
	while ((SYSCTL_PRGPIO_R&0x20) ==  0){};
	GPIO_PORTF_LOCK_R= 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x11;
	GPIO_PORTF_AFSEL_R &= ~0x11;
	GPIO_PORTF_PCTL_R &= ~0x11;
	GPIO_PORTF_AMSEL_R &= ~0x000F000F;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x11;
	GPIO_PORTF_PUR_R |= 0x11;
	GPIO_PORTF_DATA_R &= ~0x11;
}

char scan_with_clear(void){
	int row, col;
		
	GPIO_PORTE_DATA_R = 0x00; 				// enable all rows
	col = GPIO_PORTC_DATA_R & 0xF0; 	// read columns
	if(col == 0xF0)
		//return 0;												// return 0 if no key is pressed
	
	
	while(1){
		if((GPIO_PORTF_DATA_R & 0X11) == 0X01){
			return 'R';
		}
		
		if((GPIO_PORTF_DATA_R & 0X11) == 0X10){
			return 'S';
		}
		row = 0;
		GPIO_PORTE_DATA_R = 0x0E; 			// enable row 0(E0)
		delay_us(2); 										// wait for a signal to reach steady state
		col = GPIO_PORTC_DATA_R & 0xF0;
		if (col != 0xF0)								// check if there any pressed key in this row
			break;												// break if there is any pressed keys
		
		row = 1;
		GPIO_PORTE_DATA_R = 0x0D; 			// enable row 1(E1)
		delay_us(2); 										// wait for a signal to reach steady state
		col = GPIO_PORTC_DATA_R & 0xF0;
		if (col != 0xF0) 								// check if there any pressed key in this row
			break;												// break if there is any pressed keys
		
		row = 2;
		GPIO_PORTE_DATA_R = 0x0B; 			// enable row 2(E2)
		delay_us(2); 										// wait for a signal to reach steady state
		col = GPIO_PORTC_DATA_R & 0xF0;
		if (col != 0xF0)								// check if there any pressed key in this row
			break;												// break if there is any pressed keys
		
		row = 3;
		GPIO_PORTE_DATA_R = 0x07; 			// enable row 3(E3)
		delay_us(2); 										// wait for a signal to reach steady state
		col = GPIO_PORTC_DATA_R & 0xF0;
		if (col != 0xF0)								// check if there any pressed key in this row
			break;												// break if there is any pressed keys
		
		//return 0;											// return 0 if no key is pressed
	}	
		
	// return char that pressed key refer to
	if (col == 0xE0)
		return symbolmap[row][0];
	if (col == 0xD0)
		return symbolmap[row][1];
	if (col == 0xB0)
		return symbolmap[row][2];
	if (col == 0x70)
		return symbolmap[row][3];
	
	return 1;
}

