#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"
#include "core_cm3.h"
#include <stdint.h>

#define GEN_PP_10M_OUT (uint32_t)1
#define GEN_OD_10M_OUT (uint32_t)5
#define GEN_PP_2M_OUT (uint32_t)2
#define GEN_OD_2M_OUT (uint32_t)6
#define GEN_PP_50M_OUT (uint32_t)3
#define GEN_OD_50M_OUT (uint32_t)7

/* Delay func */
/* us delay has a higher precision than ms, cause latter owns an extra cond statement */
void delayus(uint32_t us);
void delayms(uint32_t ms);

#endif