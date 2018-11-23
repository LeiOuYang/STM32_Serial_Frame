
#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include "LoopQueue.h"

#define USART1_ID 	0
#define USART2_ID 	1
#define USART3_ID 	2
#define USART_MAX_ID 4

unsigned char initUsartBuff(unsigned char id);
unsigned char write(unsigned char id, char* pc, unsigned int len);
unsigned int read(unsigned char id, char* buff, unsigned int Len);
unsigned int readBuffLen(unsigned char id);
unsigned int writeBuffLen(unsigned char id);
void usartClearRxBuff(unsigned char id);
void usartClearTxBuff(unsigned char id);

char write_char(unsigned char id, char c);
char read_char(unsigned char id);

LoopQueue* getUsartSendLoopQueue(unsigned char id);
LoopQueue* getUsartRecLoopQueue(unsigned char id);

#endif
