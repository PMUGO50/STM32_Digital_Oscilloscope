#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f10x.h"
#include "core_cm3.h"
#include <stdint.h>
#include "timer.h"

#define PWM_IO GPIOA
#define PIN_PWM 2 //use GPIOA2 as PWM Pin, channel 3
#define PWMPIN_MODE 0b1011 //push-pull output, 50MHz
#define TIM_NAME TIM2
#define TIM_CKD (0b00 << 8) //clk_tds = clk_cnt, CR1
#define TIM_ARPE (0b01 << 7) //enable auto preload buffer, CR1
#define TIM_CMS (0b00 << 5) //disable center-aligned mode, CR1
#define TIM_DIR (0b00 << 4) //cnt direction: increase, CR1
#define TIM_MMS (0b100 << 4) //OC1REF as output signal, CR2
#define TIM_PSC 0 //T_clk_cnt = (TIM_PSC + 1) * T_clk_tim, PSC
#define TIM_CC3S (0b00 << 0) //channel 3 as output channel, CCMR2
#define TIM_OC3PE (0b00 << 3) //disable channel 3 preload, CCMR2
#define TIM_OC3M (0b110 << 4) //mode of channel 3: PWM1, CCMR2
#define TIM_CC3E (0b01 << 8) //enable channel 3 output, CCER
#define TIM_CC3P (0b00 << 1) //valid voltage: high, CCER
#define TIM_ARR 1024 //T_comp = TIM_ARR * T_clk_cnt, ARR
#define TIM_CCR3_INIT 256

void pwm_io_init();
void pwm_tim_init();
void pwm_init();

#endif