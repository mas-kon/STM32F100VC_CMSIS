#ifndef _USART2_H_
#define _USART2_H_

/* ============================================ INCLUDES ==================================================== */
#include "main.h"

/* ============================================ DEFINES ===================================================== */


/* ============================================ FUCTIONS ==================================================== */
void USART2_init(void);
void USART2_IRQHandler (void);
void USART2SendChar (char chr);
void USART2SendString (char* str);

#endif /* _USART2_H_ */
