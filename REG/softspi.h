#ifndef __SOFTSPI_H__
#define __SOFTSPI_H__

#include "stm32f10x.h"
#include "core_cm3.h"
#include <stdint.h>
#include "timer.h"

#define HALFT 1 //us

#define SPI_MODE GEN_PP_10M_OUT
#define SPI_IO GPIOB
#define PIN_SCK 13
#define PIN_MOSI 15
#define PIN_MISO 14

#define SCK_HIGH SPI_IO->ODR |= (0b01 << PIN_SCK)
#define SCK_LOW SPI_IO->ODR &= ~(0b01 << PIN_SCK)
#define MOSI_HIGH SPI_IO->ODR |= (0b01 << PIN_MOSI)
#define MOSI_LOW SPI_IO->ODR &= ~(0b01 << PIN_MOSI)
#define MISO_HIGH SPI_IO->ODR |= (0b01 << PIN_MISO)
#define MISO_LOW SPI_IO->ODR &= ~(0b01 << PIN_MISO)

/* SPI func */
void spi_init();
void spi_wrbyte(uint8_t data);

#endif