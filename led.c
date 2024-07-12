#include "dsco.h"

void ledinit(){
	RCC->APB2ENR = (0b01 << 4); //enable GPIOC
	GPIOC->CRH &= ~(0b1111 << ((13-8) << 2));
	GPIOC->CRH |= (GEN_PP_10M_OUT << ((13-8) << 2)); //GPIOC13: PP output
}

void ledswitch(){
	GPIOC->ODR ^= (0b01 << 13);
}

void lcd_io_init(){
	spi_init();
	//CS & DC: OD output
	if(PIN_CS>=8){
		SPI_IO->CRH &= ~(0b1111 << ((PIN_CS-8) << 2));
		SPI_IO->CRH |= (GEN_PP_10M_OUT << ((PIN_CS-8) << 2));
	}
	else{
		SPI_IO->CRL &= ~(0b1111 << (PIN_CS << 2));
		SPI_IO->CRL |= (GEN_PP_10M_OUT << (PIN_CS << 2));
	}		
	if(PIN_DC>=8){
		SPI_IO->CRH &= ~(0b1111 << ((PIN_DC-8) << 2));
		SPI_IO->CRH |= (GEN_PP_10M_OUT << ((PIN_DC-8) << 2));
	}
	else{
		SPI_IO->CRL &= ~(0b1111 << (PIN_DC << 2));
		SPI_IO->CRL |= (GEN_PP_10M_OUT << (PIN_DC << 2));
	}
	
	RCC->APB2ENR |= (0b01 << 2); //enable GPIOA
	GPIOA->ODR |= (0b00 << 8);
}

void lcd_wr_cmd(uint8_t cmd){
	CS_LOW;
  DC_C;
	spi_wrbyte(cmd);
  CS_HIGH;
}

void lcd_wr_data(uint8_t data){
	CS_LOW;
  DC_D;
	spi_wrbyte(data);
  CS_HIGH;
}

void lcd_wr_data_16(uint16_t data){
	CS_LOW;
  DC_D;
	spi_wrbyte(data >> 8);
	spi_wrbyte(data);
  CS_HIGH;
}

void lcd_init(){
	lcd_io_init();
	delayms(150); //wait for LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	lcd_wr_cmd(0x11);//Sleep exit 
	delayms(120);
		
	//ST7735R Frame Rate
	lcd_wr_cmd(0xB1); 
	lcd_wr_data(0x01); 
	lcd_wr_data(0x2C); 
	lcd_wr_data(0x2D); 

	lcd_wr_cmd(0xB2); 
	lcd_wr_data(0x01); 
	lcd_wr_data(0x2C); 
	lcd_wr_data(0x2D); 

	lcd_wr_cmd(0xB3); 
	lcd_wr_data(0x01); 
	lcd_wr_data(0x2C); 
	lcd_wr_data(0x2D); 
	lcd_wr_data(0x01); 
	lcd_wr_data(0x2C); 
	lcd_wr_data(0x2D); 
	
	lcd_wr_cmd(0xB4); //Column inversion 
	lcd_wr_data(0x07); 
	
	//ST7735R Power Sequence
	lcd_wr_cmd(0xC0); 
	lcd_wr_data(0xA2); 
	lcd_wr_data(0x02); 
	lcd_wr_data(0x84); 
	lcd_wr_cmd(0xC1); 
	lcd_wr_data(0xC5); 

	lcd_wr_cmd(0xC2); 
	lcd_wr_data(0x0A); 
	lcd_wr_data(0x00); 

	lcd_wr_cmd(0xC3); 
	lcd_wr_data(0x8A); 
	lcd_wr_data(0x2A); 
	lcd_wr_cmd(0xC4); 
	lcd_wr_data(0x8A); 
	lcd_wr_data(0xEE); 
	
	lcd_wr_cmd(0xC5); //VCOM 
	lcd_wr_data(0x0E); 
	
	lcd_wr_cmd(0x36); //MX, MY, RGB mode 
	lcd_wr_data(0xC8); 
	
	//ST7735R Gamma Sequence
	lcd_wr_cmd(0xe0); 
	lcd_wr_data(0x0f); 
	lcd_wr_data(0x1a); 
	lcd_wr_data(0x0f); 
	lcd_wr_data(0x18); 
	lcd_wr_data(0x2f); 
	lcd_wr_data(0x28); 
	lcd_wr_data(0x20); 
	lcd_wr_data(0x22); 
	lcd_wr_data(0x1f); 
	lcd_wr_data(0x1b); 
	lcd_wr_data(0x23); 
	lcd_wr_data(0x37); 
	lcd_wr_data(0x00); 	
	lcd_wr_data(0x07); 
	lcd_wr_data(0x02); 
	lcd_wr_data(0x10); 

	lcd_wr_cmd(0xe1); 
	lcd_wr_data(0x0f); 
	lcd_wr_data(0x1b); 
	lcd_wr_data(0x0f); 
	lcd_wr_data(0x17); 
	lcd_wr_data(0x33); 
	lcd_wr_data(0x2c); 
	lcd_wr_data(0x29); 
	lcd_wr_data(0x2e); 
	lcd_wr_data(0x30); 
	lcd_wr_data(0x30); 
	lcd_wr_data(0x39); 
	lcd_wr_data(0x3f); 
	lcd_wr_data(0x00); 
	lcd_wr_data(0x07); 
	lcd_wr_data(0x03); 
	lcd_wr_data(0x10);  
	
	lcd_wr_cmd(0x2a);
	lcd_wr_data(0x00);
	lcd_wr_data(0x00);
	lcd_wr_data(0x00);
	lcd_wr_data(0x7f);

	lcd_wr_cmd(0x2b);
	lcd_wr_data(0x00);
	lcd_wr_data(0x00);
	lcd_wr_data(0x00);
	lcd_wr_data(0x9f);
	
	lcd_wr_cmd(0xF0); //Enable test command  
	lcd_wr_data(0x01); 
	lcd_wr_cmd(0xF6); //Disable ram power save mode 
	lcd_wr_data(0x00); 
	
	lcd_wr_cmd(0x3A); //65k mode 
	lcd_wr_data(0x05); 
	
	
	lcd_wr_cmd(0x29);//Display on	 
}

void lcd_setregion(uint16_t x_start,uint16_t y_start, uint16_t x_end, uint16_t y_end){		
	lcd_wr_cmd(0x2a);
	lcd_wr_data(0x00);
	lcd_wr_data(x_start+2);
	lcd_wr_data(0x00);
	lcd_wr_data(x_end+2);

	lcd_wr_cmd(0x2b);
	lcd_wr_data(0x00);
	lcd_wr_data(y_start+3);
	lcd_wr_data(0x00);
	lcd_wr_data(y_end+3);
	
	lcd_wr_cmd(0x2c);
}

void lcd_point(uint16_t x, uint16_t y, uint16_t color){
	lcd_setregion(x, y, x+1, y+1);
	lcd_wr_data_16(color);
}

void lcd_clear(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){	
   unsigned int i,m;
   lcd_setregion(x1, y1, x2, y2);
   lcd_wr_cmd(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++){
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	lcd_wr_data_16(BLACK);
    }
	}
}