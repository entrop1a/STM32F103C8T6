/*
 *	TIMER functions
 *
 *	File: timer.c
 *
 *	Author: Eduardo Gomes
 *
 */

//_________________ Library _________________________________________
//___________________________________________________________________

#include "timer.h"


//_________________ Development of functions ________________________
//___________________________________________________________________

void init_pwm1_TIM2(){

	// Reset state of timer1

	TIM2 -> CR1 &= ~(TIM_CR1_CEN);							// Disable counter of TIM1
	TIM2 -> SR  &= ~(TIM_SR_UIF);							// Clean Update interrupt flag

	RCC -> APB1RSTR |=  (RCC_APB1RSTR_TIM2RST);				// Reset bus to TIM1
	RCC -> APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);				// Disable reset bus to TIM1


	// Pin configuration

	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;					// Enable clock to GPIOA

	GPIOA -> CRL &= ~(GPIO_CRL_MODE0   | GPIO_CRL_CNF0);	// Reset PA0
	GPIOA -> CRL |=   GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1;	// Set PA0 as OUTPUT (max 50 MHz)
	GPIOA -> CRL |=   GPIO_CRL_CNF0_1;						// Set PA0 as OUTPUT Alternate fuction push-pull
	GPIOA -> CRL &= ~ GPIO_CRL_CNF0_0;

	RCC -> APB1ENR |=  RCC_APB1ENR_TIM2EN;					// Enable clock to TIM1


	// PWM configuration

	TIM2 -> CR1 |= TIM_CR1_UDIS;							// Disable update of T1M1 register content with preload register

	TIM2 -> PSC = 7;
	TIM2 -> ARR = 99;
	TIM2 -> CCR1 = 50;

	TIM2 -> CR1   &= ~TIM_CR1_UDIS;							// Enable update of T1M1 register content with preload register


	// Timer configuration

	TIM2 -> CCMR1 |=  TIM_CCMR1_OC1PE;						// Enable preload CCR1
	TIM2 -> CR1   |=  TIM_CR1_ARPE;							// Enable preload ARR
	TIM2 -> CCMR1 &= ~TIM_CCMR1_CC1S;						// Set Channel 1 as OUTPUT
	TIM2 -> CCER  |=  TIM_CCER_CC1E;						// Enable Channel 1 of TIM1

	TIM2 -> EGR   |=  TIM_EGR_UG;							// Enable update of shadow register content with preload register
	TIM2 -> SR    &= ~(TIM_SR_UIF);							// Clean Update interrupt flag
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;	// Set PWM mode 1 and channel 1 is active while TIM1_CNT<TIM1_CCR1
	TIM2 -> CCER  &= ~TIM_CCER_CC1P;						// Set OUTPUT polarity active high
	TIM2 -> CR1   |=   TIM_CR1_CEN;							// Enable counter

}

