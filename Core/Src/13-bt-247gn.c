#include "13-bt-247gn.h"
#include "hv5812.h"
#include "hv57708.h"
#include "stdio.h"

Futaba247Gn device;

uint8_t internalGram[13][9] = {0};

static void delay(long tick)
{
	int i = 0;
	for (i = 0; i < tick; i++)
		;
}

void init_screen()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            internalGram[i][j] = i+1;
        }
    }
}

void scan_screen()
{
    for (size_t j = 0; j < 13; j++)
    {
        for (size_t i = 0; i < 8; i++)
            device.segment_part1[i] = internalGram[j][i];
        device.segment_part2 = internalGram[j][8];
        device.grid_part = 1 << j;
        device.reverse = 0x0;
        hv57708_dataout(device.rawbytes);
        hv5812_dataout((uint32_t *)(device.rawbytes + 8));
        hv5812_updata();
        hv57708_updata();
        delay(2000);
    }
}

void test()
{
    static long last_update_time;
    long now_tick = HAL_GetTick();
    if (now_tick - last_update_time > 500)
    {
        last_update_time = HAL_GetTick();
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                internalGram[i][j] = 0xAA;
            }
        }
    }
}
