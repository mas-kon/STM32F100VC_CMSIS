#include "USART1.h"

extern uint8_t usart1_interrupt;
extern uint8_t usart1_interrupt_dma;
char buffer_tx[]= "I am super DMA!\r\n";
char buffer_rx[8];

/* ========================================================================== */
void USART1_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;								//Enable Clock GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;             //Enable Clock for USART1
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;								//Alternate Function I/O clock enable

	// GPIOA9 - TX
	GPIOA->CRH |= GPIO_CRH_MODE9;											// Very high speed
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;										// Alternate func PUSH-PULL
	GPIOA->CRH |= GPIO_CRH_CNF9_1;										// Alternate func PUSH-PULL

	// GPIOA10 - RX
	GPIOA->CRH 	&= ~GPIO_CRH_MODE10;									// Floating input
	GPIOA->CRH 	|= GPIO_CRH_CNF10_0;									// Input floating
	GPIOA->CRH 	&= ~GPIO_CRH_CNF10_1;									// Input floating

	USART1 -> BRR = 2500; 														// 9600
	USART1 -> CR1 |= USART_CR1_RE | USART_CR1_TE;			// Enable RX, TX
	USART1 -> CR1 |= USART_CR1_UE;										// Enable USART1
	USART1 -> CR1 |= USART_CR1_RXNEIE;								// Enable IT RX
	NVIC_EnableIRQ(USART1_IRQn);											// Enable IT USART1
}
/* ========================================================================== */


void USART1_IRQHandler (void)
{
	if (USART1->SR & USART_SR_RXNE)
		{
			USART1->SR &= ~USART_SR_RXNE;	
			usart1_interrupt = 1;
		}
}

/* ========================================================================== */
void USART1SendChar (char chr)
{
	while (!(USART1->SR & USART_SR_TC));
	USART1->DR = chr;
}

/* ========================================================================== */
void USART1SendString (char* str)
{
	uint8_t i = 0;
	
	while (str[i])
	USART1SendChar(str[i++]);
}

/* ========================================================================== */

void InitDMAuart1_TX (void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	DMA1_Channel4->CPAR = (uint32_t)&USART1->DR;
	DMA1_Channel4->CMAR = (uint32_t)&buffer_tx[0];
	DMA1_Channel4->CNDTR = (sizeof(buffer_tx)-1);					// Size buffer
	
	DMA1_Channel4->CCR  &= ~DMA_CCR_CIRC;									// Disenable cycle mode
	DMA1_Channel4->CCR  &= ~DMA_CCR_PINC;									// Disenable increment pointer periphery
	
	DMA1_Channel4->CCR  &= ~DMA_CCR_PSIZE;								// Size data periphery - 8 bit
	DMA1_Channel4->CCR  &= ~DMA_CCR_MSIZE; 								// Size data memory - 8 bit
	
	DMA1_Channel4->CCR  |=  DMA_CCR_DIR;									// Read: memory -> periphery
	DMA1_Channel4->CCR  |=  DMA_CCR_MINC;									// Enable increment pointer memory
	
	USART1->CR3         |=  USART_CR3_DMAT;								// Enable DMA for USART1
}

/* ========================================================================== */

void WriteDMAuart1 (void) 
{
	DMA1_Channel4->CCR  &= ~DMA_CCR_EN;      
  DMA1_Channel4->CNDTR = (sizeof(buffer_tx)-1);      
  DMA1->IFCR          |=  DMA_IFCR_CTCIF4; 							// Status flag end of exchange
  DMA1_Channel4->CCR  |=  DMA_CCR_EN;	
}

/* ========================================================================== */

void InitDMAuart1_RX (void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	DMA1_Channel5->CPAR = (uint32_t)&(USART1->DR);
	DMA1_Channel5->CMAR = (uint32_t)&buffer_rx[0];
	DMA1_Channel5->CNDTR = 8;															// Size buffer
	
	DMA1_Channel5->CCR &= ~DMA_CCR_CIRC;									// Disenable cycle mode
	DMA1_Channel5->CCR &= ~DMA_CCR_PINC;									// Disenable increment pointer periphery
	
	DMA1_Channel5->CCR &= ~DMA_CCR_PSIZE;									// Size data periphery - 8 bit
	DMA1_Channel5->CCR &= ~DMA_CCR_MSIZE; 								// Size data memory - 8 bit
	
	DMA1_Channel5->CCR &=  ~DMA_CCR_DIR;									// Read: periphery -> memory
	DMA1_Channel5->CCR |=  DMA_CCR_MINC;									// Enable increment pointer memory
	
	DMA1_Channel5->CCR |= DMA_CCR_TCIE;										// Transfer complete interrupt enable
//	DMA1_Channel5->CCR |= DMA_CCR_TEIE;										// Transfer error interrupt enable

	DMA1_Channel5->CCR |= DMA_CCR_EN;
	
	NVIC_EnableIRQ (DMA1_Channel5_IRQn);              		// Enable IT DMA channel 5

	USART1->CR3         |=  USART_CR3_DMAR;								// Enable DMA for USART1	
}


/* ========================================================================== */

void ReadDMAuart1 (void) 
{	
	DMA1_Channel5->CCR  &= ~DMA_CCR_EN;      
  DMA1_Channel5->CNDTR = 8;      
  DMA1->IFCR          |=  DMA_IFCR_CTCIF5; 							// Status flag end of exchange
  DMA1_Channel5->CCR  |=  DMA_CCR_EN;	
}

/* ========================================================================== */

void DMA1_Channel5_IRQHandler (void)
{
 // If DMA transfer complite
 if(DMA1->ISR & DMA_ISR_TCIF5) { DMA1->IFCR |= DMA_IFCR_CTCIF5; usart1_interrupt_dma = 1; }
 // If DMA transfer error
// if(DMA1->ISR & DMA_ISR_TEIF5) { DMA1->IFCR |= DMA_IFCR_CTCIF5; GPIOPinSet(GPIOB, PIN2);}
}
