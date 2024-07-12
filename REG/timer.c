#include "timer.h"

void delayus(uint32_t us){
	SysTick->CTRL = 0b101;
	SysTick->LOAD = 72*us;
	while( !(SysTick->CTRL & 0x00010000) ); //count to zero
	SysTick->CTRL = 0b100;
}

void delayms(uint32_t ms){
	SysTick->CTRL = 0b101;
	SysTick->LOAD = 72*1000;
	while(ms){
		while( !(SysTick->CTRL & 0x00010000) ); //count to zero
		ms = ms - 1;
	}
	SysTick->CTRL = 0b100;
}