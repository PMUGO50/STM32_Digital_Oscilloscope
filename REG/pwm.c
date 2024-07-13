#include "pwm.h"

void pwm_io_init(){
	RCC->APB2ENR |= (0b01 << 2); //enable GPIOA
	if(PIN_PWM>=8){
		PWM_IO->CRH &= ~(0b1111 << ((PIN_PWM-8) << 2));
		PWM_IO->CRH |= (PWMPIN_MODE << ((PIN_PWM-8) << 2));
	}
	else{
		PWM_IO->CRL &= ~(0b1111 << (PIN_PWM << 2));
		PWM_IO->CRL |= (PWMPIN_MODE << (PIN_PWM << 2));
	}
}

void pwm_tim_init(){
	RCC->CFGR |= (0b101 << 8); //clk_apb1 = sysclk / 4 = 18MHz
	RCC->APB1ENR |= (0b01 << 0);
	TIM_NAME->CR1 |= (TIM_CKD | TIM_ARPE | TIM_CMS | TIM_DIR);
	TIM_NAME->CR2 |= TIM_MMS;
	TIM_NAME->PSC |= TIM_PSC;
	TIM_NAME->CCMR2 |= (TIM_CC3S | TIM_OC3M | TIM_OC3PE);
	TIM_NAME->CCER |= (TIM_CC3E | TIM_CC3P);
	TIM_NAME->ARR = TIM_ARR;
	TIM_NAME->CCR3 = TIM_CCR3_INIT;
}

void pwm_init(){
	pwm_io_init();
	pwm_tim_init();
	TIM_NAME->CR1 |= (0b01 << 0); //enable tim
}