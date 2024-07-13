#ifndef __DSCO_H__
#define __DSCO_H__

#include "stm32f10x.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "softspi.h"
#include "adcor.h"
#include "pwm.h"

void ledinit();
void ledswitch();

#define PIN_CS 12
#define PIN_DC 1

#define CS_HIGH SPI_IO->ODR |= (0b01 << PIN_CS)
#define CS_LOW SPI_IO->ODR &= ~(0b01 << PIN_CS)
#define DC_C SPI_IO->ODR &= ~(0b01 << PIN_DC)
#define DC_D SPI_IO->ODR |= (0b01 << PIN_DC)

#define X_MAX_PIXEL 128
#define Y_MAX_PIXEL 128
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D
#define GRAY1   0x8410
#define GRAY2   0x4208
#define LIGHTBLUE 0x05FF

#define IMG_BOTTOM 120
#define IMG_HEIGHT 70

void lcd_io_init();
void lcd_wr_cmd(uint8_t cmd);
void lcd_wr_data(uint8_t data);
void lcd_wr_data_16(uint16_t data);
void lcd_init();
void lcd_setregion(uint16_t x_start,uint16_t y_start, uint16_t x_end, uint16_t y_end);
void lcd_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_clear(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void gui_font_ascii(uint16_t x, uint16_t y, uint16_t fc, uint8_t *s);
void port_disp();
void img_disp(uint16_t* memaddr);

#endif