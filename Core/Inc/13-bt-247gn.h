#ifndef __13_BT_247GN_H__
#define __13_BT_247GN_H__

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

// Define the number of characters
#define CHAR_COUNT (95 + 1)
// 0,0	0,1	0,2	0,3	0,4
// 0,5	0,6	0,7	1,0	1,1
// 1,2	1,3	1,4	1,5	1,6
// 1,7	2,0	2,2	2,3	2,4
// 2,5	2,6	2,7	3,0	3,1
// 3,2	3,3	3,4	3,5	3,6
// 3,7	4,0	4,1	4,2	4,3

// 4,4	4,5	4,6	4,7	5,0
// 5,1	5,2	5,3	5,4	5,5
// 5,6	5,7	6,0	6,1	6,2
// 6,3	6,4	6,5	6,6	6,7
// 7,0	7,1	7,2	7,3	7,4
// 7,5	7,6	7,7	8,6	8,5
// 8,4	8,3	8,2	8,1	8,0
extern uint8_t internalGram[][9];

#define PIXEL_COUNT (20)
#define NUM_COUNT (21)
#define ICON_COUNT (51)
typedef enum
{
    Play,
    Pause,
    Cue,
    Hand,
    Acue,
    Reloop,
    Single,
    Folder,
    Mp3,
    Wma,
    Aac,
    All,
    Track,

    F,
    S,
    Colon,
    M,
    Bar_10,
    Bar_9,
    Bar_8,
    Bar_7,
    Bar_6,
    Bar_5,
    Total,
    Remain,
    Elapsed,
    Bar_1,
    Bar_2,
    Bar_3,
    Bar_4,

    Bat_6,
    Bat_5,
    Bat_4,
    Bat_3,
    Bat_2,
    Bat_1,
    Bat_0,
    Bpm,
    Auto,
    Usb,
    Sd,
    Cd,
    Lock,
    TempO,
    Key,

    L1,
    _1,
    _2,
    L2,
    L3,
    Point,
    Max
} Icon_e;

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
} Futaba247Gn_t;
extern const uint8_t hex_codes[][5];
extern const uint8_t num_hex_codes[];
/*  HV57708: G1->G13 HVOUT52->64  */
void ascii_show(int x, int y, const uint8_t *code);
void num_show(int ind, const uint8_t code);
void icon_show(Icon_e icon, bool en);
void setdimming(int val) ;
void init_screen(void);
void scan_screen(void);
void test(void);

#endif
