#include "GPIO_func.h"

/* ========================================================================== */
void GPIOPinSet(GPIO_TypeDef* _gpio, uint16_t _pin)
{	
	_gpio->BSRR |= _pin;	
}

/* ========================================================================== */
void GPIOPinReset(GPIO_TypeDef* _gpio, uint16_t _pin)
{
	_gpio->BSRR |= (_pin << 16);	
}

/* ========================================================================== */
void GPIOPinToggle(GPIO_TypeDef* _gpio, uint16_t _pin)
{
	_gpio->ODR ^= _pin ;
}

/* ========================================================================== */
uint8_t GPIOPinRead(GPIO_TypeDef* _gpio, uint16_t _pin)
{
	return ( (_gpio->IDR & _pin )== 0) ? 0: 1;
}
