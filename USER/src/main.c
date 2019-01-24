#include "main.h"

uint16_t counter = 0;
uint8_t usart1_interrupt = 0;
uint8_t usart1_interrupt_dma = 0;
uint8_t usart2_interrupt = 0;
extern char buffer_tx[];
extern char buffer_rx[8];


int main(void){

	RCC_Init();

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	Init_OUT();
	
	InitTIM6();
	InitTIM7();
	
	USART1_init();
	InitDMAuart1_TX();
	InitDMAuart1_RX();
	
//	GPIOPinSet(GPIOB, PIN2);
//	GPIOPinReset(GPIOB, PIN1);
//	GPIOPinSet(GPIOB, PIN0);
//	GPIOPinReset(GPIOC, PIN5);
//	GPIOPinSet(GPIOC, PIN4);
	
	while (1)
	{
		
		if (usart1_interrupt == 1)
		{
			usart1_interrupt = 0;
			
			ReadDMAuart1();
			
			if (buffer_rx[0] == '0')
			{
				GPIOPinReset(GPIOB, PIN0);
			}
			if (buffer_rx[0] == '1')
			{
				GPIOPinSet(GPIOB, PIN0);
			}
		}
		
		if (GPIOPinRead(GPIOC, PIN3) == 0)
			USART1SendString("BUTTON_3 \n\r");
		
		if (GPIOPinRead(GPIOC, PIN2) == 0)
			USART1SendString("BUTTON_2 \n\r");
		
	}
	
}

/* ========================================================================== */
void SysTick_Handler()
{
	counter++;
}

/* ========================================================================== */
void TIM7_IRQHandler()
{
	TIM7->SR &=~TIM_SR_UIF;
//	GPIOPinToggle(GPIOB, PIN0);
//	USART2SendString("STRING \n\r");
//	WriteDMAuart1();
}

/* ========================================================================== */
void TIM6_DAC_IRQHandler()
{	
	TIM6->SR &=~TIM_SR_UIF;
//	GPIOPinToggle(GPIOB, PIN1);
}
