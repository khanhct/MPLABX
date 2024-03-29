#include "uart.h"
/***************Ham truyen mot ky tu*********************/
void UART_SendChar(uint8_t data)
{
   /* Wait for empty transmit buffer*/
    while( !( UCSRA & (1<<UDRE)) );
    /* Put data into buffer, sends the data*/
    UDR = data;   
}
/***************Ham truyen mot chuoi ky tu*********************/
void UART_SendString(uint8_t *data)
{
    while(*data !='\0')
    {
       UART_SendChar(*data);
       data ++; 
    };
    
}
/***************Ham nhan mot ky tu*********************/
uint8_t UART_RecieveChar(void)
{
    /* Wait for data to be received*/
    while( !(UCSRA & (1<<RXC)) );
    /* Get and return received data from buffer*/
    return UDR;
}
/***************Ham nhan mot chuoi ky tu*********************/
void UART_RecieveString(uint8_t *data)
{
    *data = UART_RecieveChar();
    while(*data !='\0')
    {
        data++;
        *data = UART_RecieveChar();
    };
}
void USART_Flush(void)
{
    uint8_t dummy;
    while( UCSRA & (1<<RXC) ) dummy = UDR;
}

void ClearBuffer(uint8_t buffer[],uint8_t size)
{
    uint8_t i = 0;
    uint8_t dummy;
    for(i = 0; i<size; i++)
    buffer[i] = dummy;
}