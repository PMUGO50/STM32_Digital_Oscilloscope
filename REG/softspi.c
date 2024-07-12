#include "softspi.h"

void spi_init(){
	RCC->APB2ENR |= (0b01 << 3); //enable GPIOB
	//SCK & MOSI: OD output
	if(PIN_SCK>=8){
		SPI_IO->CRH &= ~(0b1111 << ((PIN_SCK-8) << 2));
		SPI_IO->CRH |= (SPI_MODE << ((PIN_SCK-8) << 2));
	}
	else{
		SPI_IO->CRL &= ~(0b1111 << (PIN_SCK << 2));
		SPI_IO->CRL |= (SPI_MODE << (PIN_SCK << 2));
	}
	if(PIN_MOSI>=8){
		SPI_IO->CRH &= ~(0b1111 << ((PIN_MOSI-8) << 2));
		SPI_IO->CRH |= (SPI_MODE<< ((PIN_MOSI-8) << 2));
	}		
	else{
		SPI_IO->CRL &= ~(0b1111 << (PIN_MOSI << 2));
		SPI_IO->CRL |= (SPI_MODE << (PIN_MOSI << 2));
	}
	if(PIN_MISO>=8){
		SPI_IO->CRH &= ~(0b1111 << ((PIN_MISO-8) << 2));
		SPI_IO->CRH |= (SPI_MODE<< ((PIN_MISO-8) << 2));
	}
	else{
		SPI_IO->CRL &= ~(0b1111 << (PIN_MISO << 2));
		SPI_IO->CRL |= (SPI_MODE << (PIN_MISO << 2));
	}
	MISO_HIGH;
}

void spi_wrbyte(uint8_t data){
	uint32_t i;
	for(i=8;i>0;i=i-1){
		if((data >> (i-1)) & 0b01) MOSI_HIGH;
		else MOSI_LOW;
		//delayus(HALFT);
		SCK_LOW;
		SCK_HIGH;
		//delayus(HALFT);
	}
}