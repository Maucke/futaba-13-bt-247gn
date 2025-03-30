#include "13-bt-247gn.h"
#include "hv5812.h"
#include "hv57708.h"

Futaba247Gn_t device;
//  Hexadecimal code corresponding to each character
//  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz
const uint8_t hex_codes[CHAR_COUNT][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, /*" ", 32(ASCII)*/
    {0x00, 0x00, 0x79, 0x00, 0x00}, /*"!", 33(ASCII)*/
    {0x00, 0x60, 0x00, 0x60, 0x00}, /*""", 34(ASCII)*/
    {0x22, 0x7F, 0x22, 0x7F, 0x22}, /*"#", 35(ASCII)*/
    {0x12, 0x2A, 0x7F, 0x2A, 0x24}, /*"$", 36(ASCII)*/
    {0x62, 0x64, 0x08, 0x13, 0x23}, /*"%", 37(ASCII)*/
    {0x36, 0x49, 0x35, 0x02, 0x0D}, /*"&", 38(ASCII)*/
    {0x00, 0x20, 0x40, 0x00, 0x00}, /*"'", 39(ASCII)*/
    {0x00, 0x1C, 0x22, 0x41, 0x00}, /*"(", 40(ASCII)*/
    {0x00, 0x41, 0x22, 0x1C, 0x00}, /*")", 41(ASCII)*/
    {0x14, 0x08, 0x3E, 0x08, 0x14}, /*"*", 42(ASCII)*/
    {0x08, 0x08, 0x3E, 0x08, 0x08}, /*"+", 43(ASCII)*/
    {0x00, 0x01, 0x02, 0x00, 0x00}, /*",", 44(ASCII)*/
    {0x08, 0x08, 0x08, 0x08, 0x08}, /*"-", 45(ASCII)*/
    {0x00, 0x01, 0x00, 0x00, 0x00}, /*".", 46(ASCII)*/
    {0x02, 0x04, 0x08, 0x10, 0x20}, /*"/", 47(ASCII)*/
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, /*"0", 48(ASCII)*/
    {0x00, 0x20, 0x20, 0x7F, 0x00}, /*"1", 49(ASCII)*/
    {0x23, 0x45, 0x49, 0x49, 0x31}, /*"2", 50(ASCII)*/
    {0x22, 0x41, 0x49, 0x49, 0x36}, /*"3", 51(ASCII)*/
    {0x0C, 0x14, 0x24, 0x7F, 0x04}, /*"4", 52(ASCII)*/
    {0x72, 0x51, 0x51, 0x51, 0x4E}, /*"5", 53(ASCII)*/
    {0x1E, 0x29, 0x49, 0x49, 0x06}, /*"6", 54(ASCII)*/
    {0x40, 0x40, 0x47, 0x58, 0x60}, /*"7", 55(ASCII)*/
    {0x36, 0x49, 0x49, 0x49, 0x36}, /*"8", 56(ASCII)*/
    {0x30, 0x49, 0x49, 0x4A, 0x3C}, /*"9", 57(ASCII)*/
    {0x00, 0x00, 0x11, 0x00, 0x00}, /*":", 58(ASCII)*/
    {0x00, 0x01, 0x12, 0x00, 0x00}, /*";", 59(ASCII)*/
    {0x00, 0x08, 0x14, 0x22, 0x41}, /*"<", 60(ASCII)*/
    {0x14, 0x14, 0x14, 0x14, 0x14}, /*"=", 61(ASCII)*/
    {0x41, 0x22, 0x14, 0x08, 0x00}, /*">", 62(ASCII)*/
    {0x20, 0x40, 0x45, 0x48, 0x30}, /*"?", 63(ASCII)*/
    {0x3E, 0x41, 0x4C, 0x52, 0x3E}, /*"@", 64(ASCII)*/
    {0x1F, 0x24, 0x44, 0x24, 0x1F}, /*"A", 65(ASCII)*/
    {0x41, 0x7F, 0x49, 0x49, 0x36}, /*"B", 66(ASCII)*/
    {0x3E, 0x41, 0x41, 0x41, 0x22}, /*"C", 67(ASCII)*/
    {0x41, 0x7F, 0x41, 0x41, 0x3E}, /*"D", 68(ASCII)*/
    {0x7F, 0x49, 0x49, 0x49, 0x41}, /*"E", 69(ASCII)*/
    {0x7F, 0x48, 0x48, 0x48, 0x40}, /*"F", 70(ASCII)*/
    {0x3E, 0x41, 0x49, 0x49, 0x2E}, /*"G", 71(ASCII)*/
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, /*"H", 72(ASCII)*/
    {0x00, 0x41, 0x7F, 0x41, 0x00}, /*"I", 73(ASCII)*/
    {0x02, 0x01, 0x41, 0x7F, 0x40}, /*"J", 74(ASCII)*/
    {0x7F, 0x08, 0x14, 0x22, 0x41}, /*"K", 75(ASCII)*/
    {0x7F, 0x01, 0x01, 0x01, 0x01}, /*"L", 76(ASCII)*/
    {0x7F, 0x20, 0x18, 0x20, 0x7F}, /*"M", 77(ASCII)*/
    {0x7F, 0x10, 0x08, 0x04, 0x7F}, /*"N", 78(ASCII)*/
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, /*"O", 79(ASCII)*/
    {0x7F, 0x48, 0x48, 0x48, 0x30}, /*"P", 80(ASCII)*/
    {0x3E, 0x41, 0x45, 0x42, 0x3D}, /*"Q", 81(ASCII)*/
    {0x7F, 0x48, 0x4C, 0x4A, 0x31}, /*"R", 82(ASCII)*/
    {0x32, 0x49, 0x49, 0x49, 0x26}, /*"S", 83(ASCII)*/
    {0x40, 0x40, 0x7F, 0x40, 0x40}, /*"T", 84(ASCII)*/
    {0x7E, 0x01, 0x01, 0x01, 0x7E}, /*"U", 85(ASCII)*/
    {0x78, 0x06, 0x01, 0x06, 0x78}, /*"V", 86(ASCII)*/
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, /*"W", 87(ASCII)*/
    {0x63, 0x14, 0x08, 0x14, 0x63}, /*"X", 88(ASCII)*/
    {0x70, 0x08, 0x07, 0x08, 0x70}, /*"Y", 89(ASCII)*/
    {0x43, 0x45, 0x49, 0x51, 0x61}, /*"Z", 90(ASCII)*/
    {0x00, 0x7F, 0x41, 0x41, 0x00}, /*"[", 91(ASCII)*/
    {0x20, 0x10, 0x08, 0x04, 0x02}, /*"\", 92(ASCII)*/
    {0x00, 0x41, 0x41, 0x7F, 0x00}, /*"]", 93(ASCII)*/
    {0x00, 0x20, 0x40, 0x20, 0x00}, /*"^", 94(ASCII)*/
    {0x01, 0x01, 0x01, 0x01, 0x01}, /*"_", 95(ASCII)*/
    {0x00, 0x00, 0x40, 0x20, 0x00}, /*"`", 96(ASCII)*/
    {0x02, 0x15, 0x15, 0x15, 0x0F}, /*"a", 97(ASCII)*/
    {0x7F, 0x11, 0x11, 0x11, 0x0E}, /*"b", 98(ASCII)*/
    {0x0E, 0x11, 0x11, 0x11, 0x11}, /*"c", 99(ASCII)*/
    {0x0E, 0x11, 0x11, 0x11, 0x7F}, /*"d", 100(ASCII)*/
    {0x0E, 0x15, 0x15, 0x15, 0x0D}, /*"e", 101(ASCII)*/
    {0x10, 0x10, 0x3F, 0x50, 0x50}, /*"f", 102(ASCII)*/
    {0x19, 0x25, 0x25, 0x1E, 0x20}, /*"g", 103(ASCII)*/
    {0x7F, 0x08, 0x10, 0x10, 0x0F}, /*"h", 104(ASCII)*/
    {0x00, 0x11, 0x5F, 0x01, 0x00}, /*"i", 105(ASCII)*/
    {0x02, 0x01, 0x11, 0x5E, 0x00}, /*"j", 106(ASCII)*/
    {0x00, 0x7F, 0x04, 0x0A, 0x11}, /*"k", 107(ASCII)*/
    {0x00, 0x41, 0x7F, 0x01, 0x00}, /*"l", 108(ASCII)*/
    {0x1F, 0x10, 0x0F, 0x10, 0x0F}, /*"m", 109(ASCII)*/
    {0x1F, 0x08, 0x10, 0x10, 0x0F}, /*"n", 110(ASCII)*/
    {0x0E, 0x11, 0x11, 0x11, 0x0E}, /*"o", 111(ASCII)*/
    {0x1F, 0x12, 0x12, 0x12, 0x0C}, /*"p", 112(ASCII)*/
    {0x0C, 0x12, 0x12, 0x12, 0x1F}, /*"q", 113(ASCII)*/
    {0x00, 0x1F, 0x08, 0x10, 0x10}, /*"r", 114(ASCII)*/
    {0x09, 0x15, 0x15, 0x15, 0x12}, /*"s", 115(ASCII)*/
    {0x00, 0x10, 0x7E, 0x11, 0x11}, /*"t", 116(ASCII)*/
    {0x1E, 0x01, 0x01, 0x02, 0x1F}, /*"u", 117(ASCII)*/
    {0x18, 0x06, 0x01, 0x06, 0x18}, /*"v", 118(ASCII)*/
    {0x1F, 0x02, 0x0C, 0x02, 0x1F}, /*"w", 119(ASCII)*/
    {0x11, 0x0A, 0x04, 0x0A, 0x11}, /*"x", 120(ASCII)*/
    {0x18, 0x05, 0x05, 0x05, 0x1E}, /*"y", 121(ASCII)*/
    {0x11, 0x13, 0x15, 0x19, 0x11}, /*"z", 122(ASCII)*/
    {0x00, 0x08, 0x36, 0x41, 0x00}, /*"{", 123(ASCII)*/
    {0x00, 0x00, 0x7F, 0x00, 0x00}, /*"|", 124(ASCII)*/
    {0x00, 0x41, 0x36, 0x08, 0x00}, /*"}", 125(ASCII)*/
    {0x04, 0x08, 0x0C, 0x04, 0x08}, /*"~", 126(ASCII)*/
    {0x7F, 0x7F, 0x7F, 0x7F, 0x7F},
};

// Hexadecimal code corresponding to each character
// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz
const uint8_t num_hex_codes[CHAR_COUNT] = {
    0,
    0,    // !
    0,    // "
    0,    // #
    0,    // $
    0,    // %
    0,    // &
    0,    // '
    0,    // (
    0,    // )
    0x61, // *
    0,    // +
    0,    // ,
    0,    // -
    0,    // .
    0,    // /
    0x3f, // 0
    0x06, // 1
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
    0,    // :
    0,    // ;
    0,    // <
    0,    // =
    0,    // >
    0,    // ?
    0,    // @
    0x77, // A
    0x7c, // B
    0x39, // C
    0x5e, // D
    0x79, // E
    0x71, // F
    0x6f, // G
    0x76, // H
    0x06, // I
    0x0e, // J
    0x74, // K
    0x38, // L
    0x36, // M
    0x54, // N
    0x3f, // O
    0x73, // P
    0x67, // Q
    0x50, // R
    0x6d, // S
    0x78, // T
    0x3e, // U
    0x3e, // V
    0x36, // W
    0x76, // X
    0x6e, // Y
    0x5b  // Z
};

const uint8_t pixel_positions[70][2] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {2, 0}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7}, {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7}, {8, 6}, {8, 5}, {8, 4}, {8, 3}, {8, 2}, {8, 1}, {8, 0}};

const uint8_t num_positions[7 * 21][3] = {
    // Left Area 3
    {0, 2, 0}, // a
    {0, 2, 3}, // b
    {0, 2, 6}, // c
    {0, 2, 7}, // d
    {0, 2, 5}, // e
    {0, 2, 2}, // f
    {0, 2, 4}, // g

    {0, 3, 0}, // a
    {0, 3, 2}, // b
    {0, 3, 5}, // c
    {0, 3, 6}, // d
    {0, 3, 4}, // e
    {0, 3, 1}, // f
    {0, 3, 3}, // g

    {0, 3, 7}, // a
    {0, 4, 1}, // b
    {0, 4, 4}, // c
    {0, 4, 5}, // d
    {0, 4, 3}, // e
    {0, 4, 0}, // f
    {0, 4, 2}, // g
    // Left Area 4
    {0, 5, 1}, // a
    {0, 5, 3}, // b
    {0, 5, 6}, // c
    {0, 5, 7}, // d
    {0, 5, 5}, // e
    {0, 5, 2}, // f
    {0, 5, 4}, // g

    {0, 6, 2}, // a
    {0, 6, 4}, // b
    {0, 6, 7}, // c
    {0, 7, 0}, // d
    {0, 6, 6}, // e
    {0, 6, 3}, // f
    {0, 6, 5}, // g

    {0, 7, 1}, // a
    {0, 7, 3}, // b
    {0, 7, 6}, // c
    {0, 7, 7}, // d
    {0, 7, 5}, // e
    {0, 7, 2}, // f
    {0, 7, 4}, // g

    {0, 8, 6}, // a
    {0, 8, 4}, // b
    {0, 8, 1}, // c
    {0, 8, 0}, // d
    {0, 8, 2}, // e
    {0, 8, 5}, // f
    {0, 8, 3}, // g
    // Bottom Area 3
    {1, 7, 1}, // a
    {1, 6, 7}, // b
    {1, 6, 4}, // c
    {1, 6, 3}, // d
    {1, 6, 5}, // e
    {1, 7, 0}, // f
    {1, 6, 6}, // g

    {1, 6, 2}, // a
    {1, 6, 0}, // b
    {1, 5, 5}, // c
    {1, 5, 4}, // d
    {1, 5, 6}, // e
    {1, 6, 1}, // f
    {1, 5, 7}, // g

    {1, 5, 3}, // a
    {1, 5, 1}, // b
    {1, 4, 6}, // c
    {1, 4, 5}, // d
    {1, 4, 7}, // e
    {1, 5, 2}, // f
    {1, 5, 0}, // g
    // Bottom Area 2-0
    {1, 4, 2}, // a
    {1, 4, 0}, // b
    {1, 3, 5}, // c
    {1, 3, 4}, // d
    {1, 3, 6}, // e
    {1, 4, 1}, // f
    {1, 3, 7}, // g

    {1, 3, 3}, // a
    {1, 3, 1}, // b
    {1, 2, 6}, // c
    {1, 2, 5}, // d
    {1, 2, 7}, // e
    {1, 3, 2}, // f
    {1, 3, 0}, // g
    // Bottom Area 2-1
    {1, 2, 3}, // a
    {1, 2, 0}, // b
    {1, 1, 5}, // c
    {1, 1, 4}, // d
    {1, 1, 6}, // e
    {1, 2, 2}, // f
    {1, 1, 7}, // g

    {1, 1, 3}, // a
    {1, 1, 1}, // b
    {1, 0, 6}, // c
    {1, 0, 5}, // d
    {1, 0, 7}, // e
    {1, 1, 2}, // f
    {1, 1, 0}, // g
    // Right Area 3
    {2, 2, 6}, // a
    {2, 3, 0}, // b
    {2, 3, 3}, // c
    {2, 3, 4}, // d
    {2, 3, 2}, // e
    {2, 2, 7}, // f
    {2, 3, 1}, // g

    {2, 1, 6}, // a
    {2, 2, 0}, // b
    {2, 2, 4}, // c
    {2, 2, 5}, // d
    {2, 2, 3}, // e
    {2, 1, 7}, // f
    {2, 2, 2}, // g

    {2, 0, 7}, // a
    {2, 1, 1}, // b
    {2, 1, 4}, // c
    {2, 1, 5}, // d
    {2, 1, 3}, // e
    {2, 1, 0}, // f
    {2, 1, 2}, // g
    // Right-Bottom Area 2

    {2, 7, 5}, // a
    {2, 7, 7}, // b
    {2, 8, 4}, // c
    {2, 8, 3}, // d
    {2, 8, 5}, // e
    {2, 7, 6}, // f
    {2, 8, 6}, // g
    // Right-Bottom Area 4
    {2, 6, 3}, // a
    {2, 6, 5}, // b
    {2, 7, 0}, // c
    {2, 7, 1}, // d
    {2, 6, 7}, // e
    {2, 6, 4}, // f
    {2, 6, 6}, // g

    {2, 5, 4}, // a
    {2, 5, 6}, // b
    {2, 6, 1}, // c
    {2, 6, 2}, // d
    {2, 6, 0}, // e
    {2, 5, 5}, // f
    {2, 5, 7}, // g

    {2, 4, 3}, // a
    {2, 4, 5}, // b
    {2, 5, 0}, // c
    {2, 5, 1}, // d
    {2, 4, 7}, // e
    {2, 4, 4}, // f
    {2, 4, 6}, // g
};

const uint8_t icon_positions[][3] = {
    {0, 1, 0},
    {0, 1, 1},
    {0, 1, 2},
    {0, 1, 3},
    {0, 1, 4},
    {0, 1, 5},
    {0, 1, 6},
    {0, 1, 7},
    {0, 4, 6},
    {0, 4, 7},
    {0, 5, 0},
    {0, 6, 0},
    {0, 6, 1},

    {1, 0, 4},
    {1, 2, 4},
    {1, 4, 3},
    {1, 4, 4},
    {1, 7, 2},
    {1, 7, 3},
    {1, 7, 4},
    {1, 7, 5},
    {1, 7, 6},
    {1, 7, 7},
    {1, 8, 0},
    {1, 8, 1},
    {1, 8, 2},
    {1, 8, 3},
    {1, 8, 4},
    {1, 8, 5},
    {1, 8, 6},

    {2, 0, 0},
    {2, 0, 1},
    {2, 0, 2},
    {2, 0, 3},
    {2, 0, 4},
    {2, 0, 5},
    {2, 0, 6},
    {2, 3, 5},
    {2, 3, 6},
    {2, 3, 7},
    {2, 4, 0},
    {2, 4, 1},
    {2, 4, 2},
    {2, 6, 4},

    {2, 7, 2}, // l1
    {2, 7, 3}, // _1

    {2, 8, 0}, // _2
    {2, 8, 1}, // l2
    {2, 8, 2}, // l3

    {2, 5, 2}, // h
};
uint8_t internalGram[13][9] = {0};

static void delay(long tick)
{
    int i = 0;
    for (i = 0; i < tick; i++)
        ;
}

// 10-Grid: LeftArea
// 11-Grid: BottomArea
// 12-Grid: rightArea
void init_screen()
{
    for (int i = 0; i < 13; i++)
        internalGram[i][2] = 0;
}

//  0-9-Grid: PixelArea
void ascii_show(int x, int y, const uint8_t *code) // 5byte
{
    if (x > 9 || y > 1)
        return;
    //		for(int i = 0; i < 5; i++)
    //		{
    //			printf("%x ", code[i]);
    //		}
    if (y == 0)
    {
        int index = 0;
        internalGram[x][0] = 0;
        internalGram[x][1] = 0;
        internalGram[x][2] = 0;
        internalGram[x][3] = 0;
        internalGram[x][4] &= 0xF0;
        for (int j = 6; j >= 0; j--)
        {
            for (int i = 0; i < 5; i++)
            {
                int pos_byte = pixel_positions[index][0];
                int pos_bit = pixel_positions[index][1];
                internalGram[x][pos_byte] |= ((code[i] >> j) & 1) << pos_bit;
                index++;
            }
        }
    }
    else
    {
        int index = 35;
        internalGram[x][4] &= 0xF;
        internalGram[x][5] = 0;
        internalGram[x][6] = 0;
        internalGram[x][7] = 0;
        internalGram[x][8] = 0;
        for (int j = 6; j >= 0; j--)
        {
            for (int i = 0; i < 5; i++)
            {
                int pos_byte = pixel_positions[index][0];
                int pos_bit = pixel_positions[index][1];
                internalGram[x][pos_byte] |= ((code[i] >> j) & 1) << pos_bit;
                index++;
            }
        }
    }
}

void num_show(int ind, const uint8_t code) // 1byte
{
    if (ind > 20)
        return;
    for (int j = 0; j < 7; j++)
    {
        uint8_t *pos = (uint8_t *)num_positions[ind * 7 + j];
        if ((code >> j) & 1)
            internalGram[pos[0] + 10][pos[1]] |= 1 << pos[2];
        else
            internalGram[pos[0] + 10][pos[1]] &= ~(1 << pos[2]);
    }
}

void icon_show(Icon_e icon, bool en)
{
    uint8_t *pos = (uint8_t *)icon_positions[(int)icon];
    if (en)
        internalGram[pos[0] + 10][pos[1]] |= 1 << pos[2];
    else
        internalGram[pos[0] + 10][pos[1]] &= ~(1 << pos[2]);
}

int dimming = 100;
uint8_t pixel_gram[5 * PIXEL_COUNT] = {0};
uint8_t num_gram[NUM_COUNT] = {0};
uint8_t icon_gram[ICON_COUNT] = {0};
void scan_screen()
{
    static bool screenoff = false;
    static int dimmingdamp = 0;
    if (dimmingdamp < dimming)
        dimmingdamp++;
    else if (dimmingdamp > dimming)
        dimmingdamp--;

    for (size_t i = 0; i < NUM_COUNT; i++)
        num_show(i, num_gram[i]);
    for (size_t i = 0; i < PIXEL_COUNT; i++)
    {
        ascii_show(i % 10, (i / 10) % 2, pixel_gram + 5 * i);
    }
    for (size_t i = 0; i < ICON_COUNT; i++)
    {
        icon_show((Icon_e)i, icon_gram[i]);
    }

    if (dimmingdamp > 0)
    {
        screenoff = false;
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
            delay(100 * dimmingdamp);
            memset(device.rawbytes, 0, sizeof device.rawbytes);
            device.segment_part1[2] = 0;
            hv57708_dataout(device.rawbytes);
            hv5812_dataout((uint32_t *)(device.rawbytes + 8));
            hv5812_updata();
            hv57708_updata();
            delay(10000 - 100 * dimmingdamp);
        }
    }
    else
    {
        if (screenoff)
            return;
        memset(device.rawbytes, 0, sizeof device.rawbytes);
        device.segment_part1[2] = 0;
        hv57708_dataout(device.rawbytes);
        hv5812_dataout((uint32_t *)(device.rawbytes + 8));
        hv5812_updata();
        hv57708_updata();
        screenoff = true;
    }
}

void setdimming(int val) // 0-100
{
    if (val > 100)
        dimming = 100;
    else
        dimming = val;
}

void test()
{
    static int count = 0;
    static long last_update_time;
    long now_tick = HAL_GetTick();
    if (now_tick - last_update_time > 100)
    {
        last_update_time = HAL_GetTick();

        icon_show((Icon_e)(count % (int)Max), false);
        count++;
        //        for (int i = 0; i < 13; i++)
        //        {
        //            for (int j = 0; j < 9; j++)
        //            {
        //                internalGram[i][j] = 0xAA;
        //            }
        //        }
        //        ascii_show(0, 0, (uint8_t *)hex_codes['0' - ' ' + (count / 8 / 9) % 3]);
        //        ascii_show(1, 0, (uint8_t *)hex_codes['0' - ' ' + count / 8 % 9]);
        //        ascii_show(2, 0, (uint8_t *)hex_codes['0' - ' ' + count % 8]);
        //        internalGram[(count / 8 / 9) % 3 + 10][count / 8 % 9] = 1 << (count % 8);
        for (int i = 0; i < 13; i++)
        {
            ascii_show(i, 0, hex_codes['A' - ' ' + (i + count) % 26]);
            ascii_show(i, 1, hex_codes['0' - ' ' + (i + count) % 10]);
        }
        for (int i = 0; i < 21; i++)
            num_show(i, &num_hex_codes['0' - ' ' + (count) % 10]);

        icon_show((Icon_e)(count % (int)Max), true);
        icon_show(L1, true);
    }
}
