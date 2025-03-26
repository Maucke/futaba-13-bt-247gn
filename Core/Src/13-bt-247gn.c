#include "13-bt-247gn.h"
#include "hv5812.h"
#include "hv57708.h"
#include "stdio.h"

Futaba247Gn device;

uint8_t internalGram[13][9] = {0};

static void delay()
{
	int i = 0;
	for (i = 0; i < 2560; i++)
		;
}

void init_screen()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            internalGram[i][j] = 0x55;
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
        device.grid_part = 1<<j;
        device.reverse = 0x0;
        hv57708_dataout(device.rawbytes);
        hv5812_dataout((uint32_t *)(device.rawbytes + 8));
        hv5812_updata();
        hv57708_updata();
        delay();
    }
}

void test()
{
    Futaba247Gn device;
    // 初始化 segment_part1 数组
    for (int i = 0; i < 8; i++) {
        device.segment_part1[i] = i + 1;
    }
    // 初始化位域成员
    device.grid_part = 0x556; // 13 位最大值
    device.segment_part2 = 0x67; // 7 位最大值
    device.reverse = 0; // 4 位最大值

    // 打印 rawbytes 数组的值
    printf("rawbytes:\n");
    for (size_t i = 0; i < sizeof(device.rawbytes); i++) {
        printf("  rawbytes[%zu] = %X\n", i, device.rawbytes[i]);
    }
    printf("hv5812: %X\n",*(uint32_t *)(device.rawbytes + 8));
}
