#include "dsco.h"

volatile uint32_t wait_ms = 1000;
volatile uint16_t dmem[128];

int main(){
	ledinit();
	lcd_init();
	port_disp();
	adc_init(dmem);
	while(1);
	return 0;
}

void DMA1_Channel1_IRQHandler(){
	DMA1_Channel1->CCR &= ~(0b01 << 0); //disable DMA1_Channel1
	DMA1->IFCR |= (0b01 << 1); //clear TCIF flag
	ledswitch();
	img_disp(dmem);
	ledswitch();
	delayms(wait_ms);
	DMA1->IFCR &= ~(0b01 << 1); //clear TCIF flag
	DMA1_Channel1->CCR |= (0b01 << 0); //enable DMA1_Channel1
}