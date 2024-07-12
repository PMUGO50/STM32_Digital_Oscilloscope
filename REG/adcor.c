#include "adcor.h"

void adc_io_init(){
	RCC->APB2ENR |= (0b01 << 2); //enable GPIOA
	if(PIN_ADC>=8){
		ADC_IO->CRH &= ~(0b1111 << ((PIN_ADC-8) << 2));
		ADC_IO->CRH |= (ADCPIN_MODE << ((PIN_ADC-8) << 2));
	}
	else{
		ADC_IO->CRL &= ~(0b1111 << (PIN_ADC << 2));
		ADC_IO->CRL |= (ADCPIN_MODE << (PIN_ADC << 2));
	}
}

void adc_dma_init(uint16_t* memaddr){
	RCC->AHBENR |= (0b01 << 0); //enable DMA1's clk
	DMA1_Channel1->CPAR |= (uint32_t)(&( ADC_NAME->DR ));
	DMA1_Channel1->CMAR |= (uint32_t)memaddr;
	DMA1_Channel1->CCR |= (DMA_DEV2MEM | DMA_PRIORTY_4 | DMA_MSIZE | DMA_PSIZE |
												DMA_MINC | DMA_PINC | DMA_CIRC | DMA_DIR | DMA_TCIE);
	DMA1_Channel1->CNDTR |= DMA_DNT;
}

void adc_self_init(){
	RCC->APB2ENR |= (0b01 << 9); //enable ADC1's clk
	RCC->CFGR |= (0b10 << 14); //clk_adc = clk_apb2 / 8
	ADC1->CR1 |= (ADC_MODE | ADC_SCAN);
	ADC1->CR2 |= (ADC_CONT | ADC_ETRIG | ADC_EXTSEL | ADC_ALIGN | ADC_DMA);
	ADC1->SQR3 |= ADC_SEQ;
	ADC1->SQR1 |= ADC_SEQ_NUM;
	ADC1->SMPR2 |= ADC_SAMP;
}

void nvic_init(){
	SCB->AIRCR |= NVIC_PRIORTY;
	NVIC->IP[NVIC_CHANNEL] |= NVIC_IPR;
	NVIC->ISER[NVIC_CHANNEL >> 0x05] |= (0b01 << (NVIC_CHANNEL%32));
}

void adc_init(uint16_t* memaddr){
	adc_io_init();
	adc_dma_init(memaddr);
	adc_self_init();
	nvic_init();
	DMA1_Channel1->CCR |= (0b01 << 0); //enable DMA1_Channel1
	ADC1->CR2 |= (0b01 << 0); //enable ADC1
	ADC1->CR2 |= (0b01 << 22); //trigger ADC1 on
}
