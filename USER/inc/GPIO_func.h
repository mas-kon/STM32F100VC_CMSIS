#ifndef _GPIO_H_
#define _GPIO_H_

/* ============================================ INCLUDES ===================================================== */
#include "main.h"

/* ============================================ DEFINES ===================================================== */

#define PIN0	0x0001
#define PIN1	0x0002
#define PIN2	0x0004
#define PIN3	0x0008
#define PIN4	0x0010
#define PIN5	0x0020
#define PIN6	0x0040
#define PIN7	0x0080
#define PIN8	0x0100
#define PIN9	0x0200
#define PIN10	0x0400
#define PIN11	0x0800
#define PIN12	0x1000
#define PIN13	0x2000
#define PIN14	0x4000
#define PIN15	0x8000

/* ============================================ FUCTIONS ==================================================== */

void GPIOPinSet(GPIO_TypeDef* GPIOx, uint16_t _pin);
void GPIOPinReset(GPIO_TypeDef* GPIOx, uint16_t _pin);
void GPIOPinToggle(GPIO_TypeDef* _gpio, uint16_t _pin);
uint8_t GPIOPinRead(GPIO_TypeDef* _gpio, uint16_t _pin);

#endif /* _GPIO_H_ */
