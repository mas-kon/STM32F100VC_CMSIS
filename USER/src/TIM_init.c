#include "TIM_init.h"

/* ========================================================================== */
void InitTIM7(void)
{	
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;					// Enable clock TIM7
	
	TIM7->CR1 |= TIM_CR1_ARPE;
	TIM7->PSC = 24000-1;
	TIM7->ARR = 1000-1;
	TIM7->SR |= TIM_SR_UIF;
	TIM7->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM7_IRQn);	
	TIM7->CR1 |= TIM_CR1_CEN;
}

/* ========================================================================== */
void InitTIM6(void)
{	
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;					// Enable clock TIM6
	
	TIM6->CR1 |= TIM_CR1_ARPE;
	TIM6->PSC = 24000-1;
	TIM6->ARR = 500-1;
	TIM6->SR |= TIM_SR_UIF;
	TIM6->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM6_DAC_IRQn);	
	TIM6->CR1 |= TIM_CR1_CEN;
}
