#include <avr/io.h>
#include "avrsub.h"

void wait(volatile unsigned long ll)
{
    while (ll--)
        ;
}
void init_USART(unsigned int rate)
{
    DDRD = 0xFB;
    UCSR1A = 0x00;
    UCSR1B = 0x18;
    UCSR1C = 0x06;
    if (rate == 9600)
    {
        UBRRH = 0x00;
        UBRR1L = 47;
    }
    else if (rate == 19200)
    {
        UBRRH = 0x00;
        UBRR1L = 23;
    }
    else if (rate == 57600)
    {
        UBRRH = 0x00;
        UBRR1L = 7;
    }
    else if (rate == 115200)
    {
        UBRRH = 0x00;
        UBRR1L = 3;
    }
    else
    {
        UBRRH = 0x00;
        UBRR1L = 47;
    }
}
void init_ADC(byte ad_channel)
{
    ADMUX |= 0x40;
    ADMUX |= ((ADMUX & 0xE0) | ad_channel);
    ADCSRA |= 0x02;
    ADCSRA |= (1 << ADFR);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
}
unsigned int adc()
{
    while (!(ADCSRA & 0x10))
        ;
    ADCSRA |= 0x10;
    return (ADCW);
}
void putch(char data)
{
    while (!(UCSR1A & 0x20))
        ;
    UDR1 = data;
}
void dat_send(int x, int y)
{
    byte i = 0;
    volatile char *text = "1234 5678\n";

    text[0] = (byte)(x / 1000) + 48;
    text[1] = (byte)((x % 1000) / 100) + 48;
    text[2] = (byte)((x % 100) / 10) + 48;
    text[3] = (byte)(x % 10) + 48;
    text[5] = (byte)(y / 1000) + 48;
    text[6] = (byte)((y % 1000) / 100) + 48;
    text[7] = (byte)((y % 100) / 10) + 48;
    text[8] = (byte)(y % 10) + 48;

    while (text[i] != '\0')
        putch(text[i++]);
}