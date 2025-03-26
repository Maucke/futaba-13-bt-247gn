#ifndef __13_BT_247GN_H__
#define __13_BT_247GN_H__

#include "stm32f4xx_hal.h"

extern uint8_t internalGram[][9];

typedef union
{
    struct
    {
        uint8_t segment_part1[8];
        struct
        {
            uint32_t grid_part : 13;
            uint32_t segment_part2 : 7;
            uint32_t reverse : 4;
        };
    };
    uint8_t rawbytes[12];
} Futaba247Gn;

/*  HV57708: G1->G13 HVOUT52->64  */
void init_screen(void);
void scan_screen(void);
void test(void);

#endif
