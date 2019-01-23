#ifndef _USART1_H_
#define _USART1_H_

/* ============================================ INCLUDES ==================================================== */
#include "main.h"

/* ============================================ DEFINES ===================================================== */


/* ============================================ FUCTIONS ==================================================== */
void USART1_init(void);
void USART1_IRQHandler (void);
void USART1SendChar (char chr);
void USART1SendString (char* str);
void InitDMAuart1_TX (void);
void InitDMAuart1_RX (void);
void WriteDMAuart1 (void);
void ReadDMAuart1 (void);
void DMA1_Channel5_IRQHandler (void);

#endif /* _USART1_H_ */
