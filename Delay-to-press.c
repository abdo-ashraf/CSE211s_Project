#include "prototype&header.h"



void delay_SW1_ms(unsigned int times, int* x){		//delay with check if switch 1 is pressed or not and then break when pressed
				unsigned int i;
				
				for(i=0; i < times; i++){
					NVIC_ST_CTRL_R = 0x0;
					NVIC_ST_RELOAD_R = 16000-1;		//using the reload value to delay one millisecond
					NVIC_ST_CURRENT_R = 0x0;
					NVIC_ST_CTRL_R = 0x5;
					while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
					if((GPIO_PORTF_DATA_R & 0x10) == 0){		//check for switch 1 statue
						*x = 1;
						goto end;
					}
				}
end:		;
}



void delay_SW2_ms(unsigned int times, int* x){		//delay with check if switch 2 is pressed or not and then break when pressed
				unsigned int i;
				
				for(i=0; i < times; i++){
					NVIC_ST_CTRL_R = 0x0;
					NVIC_ST_RELOAD_R = 16000-1;		//using the reload value to delay one millisecond
					NVIC_ST_CURRENT_R = 0x0;
					NVIC_ST_CTRL_R = 0x5;
					while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
					if((GPIO_PORTF_DATA_R & 0x01) == 0){		//check for switch 2 statue
						*x = 2;
						goto end;
					}
				}
end:    ;
}


void delay_SW3_ms(unsigned int times, int* x){		//delay with check if the door is opened or not and then break when opened
				unsigned int i;
				
				for(i=0; i < times; i++){
					NVIC_ST_CTRL_R = 0x0;
					NVIC_ST_RELOAD_R = 16000-1;		//using the reload value to delay one millisecond
					NVIC_ST_CURRENT_R = 0x0;
					NVIC_ST_CTRL_R = 0x5;
					while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
						
					if((GPIO_PORTE_DATA_R & 0x20) != 0){		//check for the door statue
						*x = 3;
						goto end;
					}
				}
end:    ;
}


void delay_SW1_SW2_ms(unsigned int times, int* x){		//delay with check if switch 1 or 2 is pressed or not and then break when pressed
				unsigned int i;
				
				for(i=0; i < times; i++){
					NVIC_ST_CTRL_R = 0x0;
					NVIC_ST_RELOAD_R = 16000-1;		//using the reload value to delay one millisecond
					NVIC_ST_CURRENT_R = 0x0;
					NVIC_ST_CTRL_R = 0x5;
					while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
					if((GPIO_PORTF_DATA_R & 0x10) == 0){		//check for switch 1 and 2 statues
						*x = 1;
						goto end;
					}
					else if(((GPIO_PORTF_DATA_R & 0x01) == 0) && ((GPIO_PORTE_DATA_R & 0x20) != 0)){
						*x = 2;
						goto end;
					}
				}
end:    ;
}


void delay_SW1_SW3_ms(unsigned int times, int* x){		//delay with check if switch 1 is pressed or the door is opened not and then break when press the botton or open the door
				unsigned int i;
				
				for(i=0; i < times; i++){
					NVIC_ST_CTRL_R = 0x0;
					NVIC_ST_RELOAD_R = 16000-1;		//using the reload value to delay one millisecond
					NVIC_ST_CURRENT_R = 0x0;
					NVIC_ST_CTRL_R = 0x5;
					while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
					if((GPIO_PORTF_DATA_R & 0x10) == 0){		//check for switch 1 and the door statues
						*x = 1;
						goto end;
					}
					else if((GPIO_PORTE_DATA_R & 0x20) == 0){
						*x = 3;
						goto end;
					}
				}
end:    ;
}

