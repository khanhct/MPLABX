#ifndef __UART_H
#define __UART_H

#include "RF433Router.h"
/***************Ham truyen mot ky tu*********************/
void UART_SendChar(uint8_t data);
/***************Ham truyen mot chuoi ky tu*********************/
void UART_SendString(uint8_t *data);
/***************Ham nhan mot ky tu*********************/
uint8_t UART_RecieveChar(void);
/***************Ham nhan mot chuoi ky tu*********************/
void UART_RecieveString(uint8_t *data);
void ClearBuffer(uint8_t buffer[],uint8_t size);
void USART_Flush(void);

#endif