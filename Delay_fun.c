#include "prototype&header.h"


void delay_us(unsigned int times){
	unsigned int i;
	//initialization of timer with microsecond scale
	for(i=0; i < times; i++){
		NVIC_ST_CTRL_R = 0x0;
		NVIC_ST_RELOAD_R = 16-1;		//set the reload value to be counted down to make one microsecond delay
		NVIC_ST_CURRENT_R = 0x0;
		NVIC_ST_CTRL_R = 0x5;
		while((NVIC_ST_CTRL_R & 0x00010000) == 0){} //wait for the counter to finish the reload value
	}
}

void delay_ms(unsigned int times){
	unsigned int i;
	//initialization of timer with millisecond scale
	for(i=0; i < times; i++){
		NVIC_ST_CTRL_R = 0x0;
		NVIC_ST_RELOAD_R = 16000-1;		//set the reload value to be counted down to make one millisecond delay
		NVIC_ST_CURRENT_R = 0x0;
		NVIC_ST_CTRL_R = 0x5;
		while((NVIC_ST_CTRL_R & 0x00010000) == 0){} //wait for the counter to finish the reload value
	}
}

void delay_sec(unsigned int times){
	unsigned int i;
	//initialization of timer with one second scale
	for(i = 0; i < times; i++){
		NVIC_ST_CTRL_R = 0x0;
		NVIC_ST_RELOAD_R = 16000000-1;		//set the reload value to be counted down to make one second delay
		NVIC_ST_CURRENT_R = 0x0;
		NVIC_ST_CTRL_R = 0x5;
		while((NVIC_ST_CTRL_R & 0x00010000) == 0){} //wait for the counter to finish the reload value
	}
}
