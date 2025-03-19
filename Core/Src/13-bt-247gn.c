#include "13-bt-247gn.h"
#include "hv5812.h"
#include "hv57708.h"
#include "stm32f4xx_hal.h"

unsigned char gram[8 + 3] = {0};

void test()
{
    unsigned char i = 0;
    unsigned short *grid = (unsigned short *)(gram + 6);
    for (i = 0; i < 11; i++)
    {
        gram[i] = 0xff;
    }

    for (i = 0; i < 13; i++)
    {
        *grid = 7 | (1 << i);

        hv57708_dataout(gram + 8);
        hv5812_dataout(gram);
        HAL_Delay(100);
    }
}