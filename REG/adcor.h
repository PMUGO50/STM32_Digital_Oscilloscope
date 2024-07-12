#ifndef __ADCOR_H__
#define __ADCOR_H__

#include "stm32f10x.h"
#include "core_cm3.h"
#include <stdint.h>
#include "timer.h"

#define SAMPT 0b000
#if SAMPT==0b000
#define SAMPCHAR "1.17us" //14 * (1/12)us, ans * 128 = 149.3us 
#elif SAMPT==0b001
#define SAMPCHAR "1.67us" //20 * (1/12)us, ans * 128 = 213.3us
#elif SAMPT==0b010
#define SAMPCHAR "2.17us" //26 * (1/12)us, ans * 128 = 277.3us
#elif SAMPT==0b011
#define SAMPCHAR "3.42us" //41 * (1/12)us, ans * 128 = 437.3us
#elif SAMPT==0b100
#define SAMPCHAR "4.50us" //54 * (1/12)us, ans * 128 = 576.0us
#elif SAMPT==0b101
#define SAMPCHAR "5.67us" //68 * (1/12)us, ans * 128 = 725.3us
#elif SAMPT==0b110
#define SAMPCHAR "7.00us" //84 * (1/12)us, ans * 128 = 896.0us
#elif SAMPT==0b111
#define SAMPCHAR "21.0us" //252 * (1/12)us, ans * 128 = 2688.0us
#else
#define SAMPCHAR "error"
#endif

#define ADC_IO GPIOA
#define PIN_ADC 1 //use GPIOA1 as ADC Pin, channel 1
#define ADCPIN_MODE 0b0000
#define ADC_NAME ADC1
#define ADC_MODE (0b0000 << 16) //independent mode, CR1
#define ADC_SCAN (0b00 << 8) //scan mode, CR1
#define ADC_CONT (0b01 << 1) //continous convert, CR2
#define ADC_ETRIG (0b01 << 20) //disable exit trigger, CR2
#define ADC_EXTSEL (0b111 << 17) //external trig select as software, CR2
#define ADC_ALIGN (0b00 << 11) //right align, CR2
#define ADC_DMA (0b01 << 8) //DMA, CR2
#define ADC_SEQ (0b00001 << 0) //conversion set to channel 1, SQR3
#define ADC_SEQ_NUM (0b0000 << 20) //num of conversion is 1, SQR1
#define ADC_SAMP (SAMPT << 3) //sampling period of conversion (channel 1), SMPR2

#define DMA_DEV2MEM (0b00 << 14) //device to mem, CCR
#define DMA_PRIORTY_4 (0b11 << 12) //highest priorty, CCR
#define DMA_MSIZE (0b01 << 10) //16bit mem, CCR
#define DMA_PSIZE (0b10 << 8) //32bit dev(ADC->DR), CCR
#define DMA_MINC (0b01 << 7) //mem increase enable, CCR
#define DMA_PINC (0b00 << 6) //dev increase disable, CCR
#define DMA_CIRC (0b01 << 5) //circling mode, CCR
#define DMA_DIR (0b00 << 4) //read from device, CCR
#define DMA_TCIE (0b01 << 1) //enable transfer complete interrupt, CCR
#define DMA_DNT 0b01111111 //num of trans data, CNDTR

#define NVIC_PRIORTY (0b011 << 8) //priorty group: 4, SCB
#define NVIC_CHANNEL 11 //DMA1 nvic-channel code
#define NVIC_IPR (0b0000 << 4) //priorty: highest

void adc_io_init();
void adc_dma_init(uint16_t* memaddr);
void adc_self_init();
void nvic_init();
void adc_init(uint16_t* memaddr);

#endif