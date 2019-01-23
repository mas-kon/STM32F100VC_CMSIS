#include "GPIO_init.h"

/* ========================================================================== */
void Init_OUT(void){
	
	/* Enable RCC GPIO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		
	/* Configure GPIOB0 as output, meduim speed, push-pull */
	GPIOB->CRL &= ~GPIO_CRL_CNF0;
	GPIOB->CRL |= GPIO_CRL_MODE0_0;
	GPIOB->CRL &= ~GPIO_CRL_MODE0_1;
	
	/* Configure GPIOB1 as output, meduim speed, push-pull */
	GPIOB->CRL &= ~GPIO_CRL_CNF1;
	GPIOB->CRL |= GPIO_CRL_MODE1_0;
	GPIOB->CRL &= ~GPIO_CRL_MODE1_1;
	
	/* Configure GPIOB2 as output, meduim speed, push-pull */
	GPIOB->CRL &= ~GPIO_CRL_CNF2;
	GPIOB->CRL |= GPIO_CRL_MODE2_0;
	GPIOB->CRL &= ~GPIO_CRL_MODE2_1;
	
	/* Configure GPIOC5 as output, meduim speed, push-pull */
	GPIOC->CRL &= ~GPIO_CRL_CNF5;
	GPIOC->CRL |= GPIO_CRL_MODE5_0;
	GPIOC->CRL &= ~GPIO_CRL_MODE5_1;
	
	/* Configure GPIOC4 as output, meduim speed, push-pull */
	GPIOC->CRL &= ~GPIO_CRL_CNF4;
	GPIOC->CRL |= GPIO_CRL_MODE4_0;
	GPIOC->CRL &= ~GPIO_CRL_MODE4_1;
	
}
void Init_INPUT(void){
	/* Enable RCC GPIO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	/* Configure GPIOC3 as input, floating */
	GPIOC->CRL |= GPIO_CRL_CNF3_0;
	GPIOC->CRL &= ~GPIO_CRL_CNF3_1;
	GPIOC->CRL &= ~GPIO_CRL_MODE3;
	/* Configure GPIOC2 as input, floating */
	GPIOC->CRL |= GPIO_CRL_CNF2_0;
	GPIOC->CRL &= ~GPIO_CRL_CNF2_1;
	GPIOC->CRL &= ~GPIO_CRL_MODE2;

	/* Configure GPIOC1 as input, floating */
	GPIOC->CRL |= GPIO_CRL_CNF1_0;
	GPIOC->CRL &= ~GPIO_CRL_CNF1_1;
	GPIOC->CRL &= ~GPIO_CRL_MODE1;
	
	/* Configure GPIOC0 as input, floating */
	GPIOC->CRL |= GPIO_CRL_CNF0_0;
	GPIOC->CRL &= ~GPIO_CRL_CNF0_1;
	GPIOC->CRL &= ~GPIO_CRL_MODE0;
	
}
