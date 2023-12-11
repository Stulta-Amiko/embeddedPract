#ifndef AVRSUB_H_
#define AVRSUB_H_

typedef unsigned char byte;
#define sbit(x, y) (x |= (1 << y))
#define cbit(x, y) (x &= ~(1 << y))
#define tbit(x, y) (x & (1 << y))

void wait(volatile unsigned long);
void init_USART(unsigned int);
void init_ADC(byte ad_channel);
unsigned int adc();
void putch(char data);
void dat_send(int x, int y);

#endif AVRSUB_H_