#include <avr/io.h>
#include "avrsub.h"
#define ORDER 4

float hn[2][ORDER + 1] = {
    {0.2, 0.2, 0.2, 0.2, 0.2}, {1, 2, -6, 2, 1}};

int main()
{
    unsigned int flag = 0;
    unsigned int cth = 100;
    unsigned int xn[ORDER + 1], yn;
    float acc;

    sbit(PORTB, PB4);
    DDRB |= 0x10;
    DDRC &= ~0xF0;
    DDRD = 0xFB;
    TCCR0 = 0x61;
    TCNT0 = 0;

    OCR0 = cth;

    for (int i = 0; i <= ORDER; i++)
        xn[i] = 512;
    init_USART(57600);
    init_ADC(0);

    while (1)
    {
        xn[0] = adc();

        if (tbit(PINC, PC5))
        {
            cth -= 2;
            if (cth <= 5)
                cth = 5;
        }
        if (tbit(PINC, PC6))
        {
            if (flag)
                flag = 0;
            else
                flag = 1;
            while (tbit(PINC, PC6))
                ;
        }
        if (tbit(PINC, PC7))
        {
            cth += 2;
            if (cth > 250)
                cth = 255;
        }

        acc = 0.0;
        OCR0 = cth;
        for (int i = 0; i <= ORDER; i++)
            acc = acc + xn[i] * hn[flag][i];
        if (acc < 0.0)
            yn = 0;
        else if (acc > 1023.0)
            yn = 1023;
        else
            yn = (unsigned int)acc;

        dat_send(xn[0], yn);
        for (int i = ORDER; i > 0; i--)
            xn[i] = xn[i - 1];
        wait(0x8000);
    }
    return 0;
}