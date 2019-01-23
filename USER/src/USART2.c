#include "USART2.h"

extern uint8_t usart2_interrupt;

/* ========================================================================== */
void USART2_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;								//Enable Clock GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;             //Enable Clock for USART2
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;								//Alternate Function I/O clock enable

	// GPIOA2 - TX
	GPIOA->CRL |= GPIO_CRL_MODE2;											// Very high speed
	GPIOA->CRL &= ~GPIO_CRL_CNF2_0;										// Alternate func PUSH-PULL
	GPIOA->CRL |= GPIO_CRL_CNF2_1;										// Alternate func PUSH-PULL

	// GPIOA3 - RX
	GPIOA->CRL 	&= ~GPIO_CRL_MODE3;										// Floating input
	GPIOA->CRL 	|= GPIO_CRL_CNF3_0;										// Input floating
	GPIOA->CRL 	&= ~GPIO_CRL_CNF3_1;									// Input floating

	USART2 -> BRR = 0x9c4;														// 9600
	USART2 -> CR1 |= USART_CR1_RE | USART_CR1_TE;			// Enable RX, TX
	USART2 -> CR1 |= USART_CR1_UE;										// Enable USART2
	USART2 -> CR1 |= USART_CR1_RXNEIE;								// Enable IT RX
	NVIC_EnableIRQ(USART2_IRQn);											// Enable IT USART2
}
/* ========================================================================== */


void USART2_IRQHandler (void)
{
	if (USART2->SR & USART_SR_RXNE)
		{
			USART2->SR &= ~USART_SR_RXNE;	
			usart2_interrupt = 1;
		}
}

/* ========================================================================== */
void USART2SendChar (char chr)
{
	while (!(USART2->SR & USART_SR_TC));
	USART2->DR = chr;
}

/* ========================================================================== */
void USART2SendString (char* str)
{
	uint8_t i = 0;
	
	while (str[i])
	USART2SendChar(str[i++]);
}
