/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font /Users/davidburke/SquareLine/assets/Courier New.ttf -o /Users/davidburke/SquareLine/assets/ui_font_Courier_New_16.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_COURIER_NEW_16
#define UI_FONT_COURIER_NEW_16 1
#endif

#if UI_FONT_COURIER_NEW_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xaa, 0xa0, 0x30,

    /* U+0022 "\"" */
    0xcb, 0x2c, 0x92,

    /* U+0023 "#" */
    0x28, 0x50, 0xa1, 0x47, 0xe5, 0xa, 0x7f, 0x28,
    0x50, 0xa1, 0x40,

    /* U+0024 "$" */
    0x10, 0x79, 0x92, 0x4, 0x7, 0x1, 0xc1, 0xc6,
    0x78, 0x40, 0x80,

    /* U+0025 "%" */
    0x30, 0x91, 0x21, 0x80, 0x67, 0x13, 0x9, 0x12,
    0x18,

    /* U+0026 "&" */
    0x39, 0x4, 0x10, 0x23, 0x59, 0x62, 0x74,

    /* U+0027 "'" */
    0xfa,

    /* U+0028 "(" */
    0x29, 0x49, 0x24, 0x89, 0x10,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x29, 0x40,

    /* U+002A "*" */
    0x10, 0x21, 0xf0, 0x82, 0x80, 0x0,

    /* U+002B "+" */
    0x0, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x0,

    /* U+002C "," */
    0x76, 0x64, 0x80,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x20, 0x84, 0x10, 0x82, 0x10, 0x41, 0x8,
    0x20,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x49, 0xe0,

    /* U+0031 "1" */
    0x30, 0xa0, 0x40, 0x81, 0x2, 0x4, 0x8, 0x11,
    0xfc,

    /* U+0032 "2" */
    0x38, 0x8c, 0x8, 0x10, 0x41, 0x4, 0x10, 0x43,
    0xfc,

    /* U+0033 "3" */
    0x3c, 0x8c, 0x8, 0x31, 0xc0, 0xc0, 0x81, 0x84,
    0xf0,

    /* U+0034 "4" */
    0xc, 0x28, 0x51, 0x24, 0x48, 0xbf, 0x82, 0x4,
    0x3c,

    /* U+0035 "5" */
    0x7c, 0x81, 0x3, 0xe4, 0x60, 0x40, 0x81, 0xc4,
    0x70,

    /* U+0036 "6" */
    0x1d, 0x84, 0x20, 0xbb, 0x38, 0x61, 0x8d, 0xe0,

    /* U+0037 "7" */
    0xff, 0x4, 0x8, 0x20, 0x40, 0x82, 0x4, 0x10,
    0x20,

    /* U+0038 "8" */
    0x7b, 0x38, 0x73, 0x39, 0x28, 0x61, 0xcd, 0xe0,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0xcd, 0xd0, 0x43, 0x1b, 0x80,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0x6c, 0x6, 0xb4, 0x0,

    /* U+003C "<" */
    0x2, 0x18, 0xc2, 0xc, 0x6, 0x3, 0x1,

    /* U+003D "=" */
    0xff, 0x0, 0xff,

    /* U+003E ">" */
    0xc0, 0x20, 0x18, 0x6, 0x2, 0xc, 0x30, 0xc0,

    /* U+003F "?" */
    0x7a, 0x38, 0x41, 0x8, 0xc2, 0x0, 0x30,

    /* U+0040 "@" */
    0x39, 0x18, 0x67, 0xb6, 0x9a, 0x67, 0x81, 0x3,
    0x80,

    /* U+0041 "A" */
    0x3c, 0x5, 0x1, 0x40, 0x48, 0x22, 0xf, 0xc4,
    0x11, 0x4, 0xe3, 0xc0,

    /* U+0042 "B" */
    0xfc, 0x42, 0x42, 0x42, 0x7c, 0x43, 0x41, 0x43,
    0xfe,

    /* U+0043 "C" */
    0x3d, 0x43, 0x80, 0x80, 0x80, 0x80, 0xc1, 0x62,
    0x3c,

    /* U+0044 "D" */
    0xfc, 0x42, 0x41, 0x41, 0x41, 0x41, 0x41, 0x42,
    0xfc,

    /* U+0045 "E" */
    0xfe, 0x42, 0x42, 0x48, 0x78, 0x48, 0x41, 0x41,
    0xff,

    /* U+0046 "F" */
    0xff, 0x41, 0x41, 0x48, 0x78, 0x48, 0x40, 0x40,
    0xf8,

    /* U+0047 "G" */
    0x3d, 0x31, 0xb0, 0x10, 0x8, 0x4, 0x7e, 0x4,
    0x82, 0x3e, 0x0,

    /* U+0048 "H" */
    0xe7, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42,
    0xe7,

    /* U+0049 "I" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0xfe,

    /* U+004A "J" */
    0x3f, 0x4, 0x4, 0x4, 0x4, 0x84, 0x84, 0xcc,
    0x78,

    /* U+004B "K" */
    0xf7, 0x21, 0x11, 0xb, 0x6, 0x82, 0x21, 0x8,
    0x84, 0xf1, 0x80,

    /* U+004C "L" */
    0xf8, 0x20, 0x20, 0x20, 0x20, 0x21, 0x21, 0x21,
    0xff,

    /* U+004D "M" */
    0xe1, 0xd8, 0x65, 0x29, 0x4a, 0x4c, 0x93, 0x24,
    0x9, 0x2, 0xf3, 0xc0,

    /* U+004E "N" */
    0xc7, 0xb0, 0x94, 0x4a, 0x24, 0x92, 0x29, 0x14,
    0x86, 0xf3, 0x0,

    /* U+004F "O" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0xc3, 0x42,
    0x3c,

    /* U+0050 "P" */
    0xfc, 0x8d, 0xa, 0x37, 0xc8, 0x10, 0x20, 0xf8,

    /* U+0051 "Q" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0xc3, 0x42,
    0x3c, 0x1d, 0x26,

    /* U+0052 "R" */
    0xfc, 0x46, 0x42, 0x46, 0x78, 0x44, 0x44, 0x42,
    0xf1,

    /* U+0053 "S" */
    0x7b, 0x8e, 0x4, 0x7, 0x80, 0xc0, 0xc3, 0xfc,

    /* U+0054 "T" */
    0xff, 0x26, 0x48, 0x81, 0x2, 0x4, 0x8, 0x7c,

    /* U+0055 "U" */
    0xf7, 0xa0, 0x90, 0x48, 0x24, 0x12, 0x9, 0x4,
    0xc6, 0x3e, 0x0,

    /* U+0056 "V" */
    0xe3, 0xa0, 0x90, 0x44, 0x22, 0x20, 0x90, 0x50,
    0x28, 0xc, 0x0,

    /* U+0057 "W" */
    0xf3, 0xa0, 0x52, 0x49, 0xa5, 0x52, 0xa9, 0x4c,
    0xc6, 0x21, 0x0,

    /* U+0058 "X" */
    0xc7, 0x42, 0x24, 0x28, 0x10, 0x28, 0x44, 0x42,
    0xe7,

    /* U+0059 "Y" */
    0xe3, 0xa1, 0x8, 0x82, 0x80, 0x80, 0x40, 0x20,
    0x10, 0x3e, 0x0,

    /* U+005A "Z" */
    0x7c, 0x89, 0x10, 0x41, 0x4, 0x18, 0xa1, 0xfe,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x70,

    /* U+005C "\\" */
    0x82, 0xc, 0x10, 0x40, 0x82, 0x4, 0x10, 0x20,
    0x81,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0xf0,

    /* U+005E "^" */
    0x21, 0x48, 0xa1,

    /* U+005F "_" */
    0xff, 0xc0,

    /* U+0060 "`" */
    0x8, 0x80,

    /* U+0061 "a" */
    0x78, 0x9, 0xf6, 0x28, 0x51, 0x9d, 0x80,

    /* U+0062 "b" */
    0xc0, 0x40, 0x40, 0x5c, 0x62, 0x41, 0x41, 0x41,
    0x62, 0xdc,

    /* U+0063 "c" */
    0x3e, 0x42, 0x80, 0x80, 0x80, 0x42, 0x3c,

    /* U+0064 "d" */
    0x6, 0x2, 0x2, 0x3a, 0x46, 0x82, 0x82, 0x82,
    0x46, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x42, 0x82, 0xfe, 0x80, 0x42, 0x3c,

    /* U+0066 "f" */
    0x1e, 0x40, 0x87, 0xf2, 0x4, 0x8, 0x10, 0x21,
    0xf8,

    /* U+0067 "g" */
    0x3b, 0x46, 0x82, 0x82, 0x82, 0x46, 0x3a, 0x2,
    0x6, 0x3c,

    /* U+0068 "h" */
    0xc0, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42,
    0x42, 0xe7,

    /* U+0069 "i" */
    0x10, 0x0, 0x3, 0x81, 0x2, 0x4, 0x8, 0x11,
    0xfc,

    /* U+006A "j" */
    0x10, 0x1, 0xf0, 0x84, 0x21, 0x8, 0x42, 0x3f,
    0x0,

    /* U+006B "k" */
    0xc0, 0x40, 0x40, 0x4e, 0x48, 0x50, 0x70, 0x48,
    0x44, 0xc7,

    /* U+006C "l" */
    0x70, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x11,
    0xfc,

    /* U+006D "m" */
    0xf7, 0x24, 0x92, 0x49, 0x24, 0x92, 0x4b, 0xb6,

    /* U+006E "n" */
    0xdc, 0x62, 0x42, 0x42, 0x42, 0x42, 0xe7,

    /* U+006F "o" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+0070 "p" */
    0xdc, 0x62, 0x41, 0x41, 0x41, 0x62, 0x5c, 0x40,
    0x40, 0xf0,

    /* U+0071 "q" */
    0x3b, 0x46, 0x82, 0x82, 0x82, 0x46, 0x3a, 0x2,
    0x2, 0xf,

    /* U+0072 "r" */
    0xe6, 0x38, 0x20, 0x20, 0x20, 0x20, 0xfc,

    /* U+0073 "s" */
    0x3c, 0x89, 0x1, 0xe0, 0x30, 0xff, 0x0,

    /* U+0074 "t" */
    0x20, 0x20, 0xfe, 0x20, 0x20, 0x20, 0x20, 0x21,
    0x1e,

    /* U+0075 "u" */
    0xce, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3b,

    /* U+0076 "v" */
    0xf3, 0x90, 0x88, 0x84, 0x41, 0x20, 0xa0, 0x30,

    /* U+0077 "w" */
    0xe3, 0xa0, 0x92, 0x49, 0xa3, 0x51, 0xb0, 0xc8,

    /* U+0078 "x" */
    0xe6, 0x44, 0x28, 0x10, 0x2c, 0x42, 0xe7,

    /* U+0079 "y" */
    0xe3, 0x42, 0x42, 0x24, 0x24, 0x18, 0x8, 0x10,
    0x10, 0xf8,

    /* U+007A "z" */
    0xfe, 0x21, 0x8, 0x41, 0x1f, 0xc0,

    /* U+007B "{" */
    0x29, 0x25, 0xb2, 0x49, 0x10,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x89, 0x24, 0xda, 0x49, 0x40,

    /* U+007E "~" */
    0x61, 0x24, 0x30
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 154, .box_w = 2, .box_h = 10, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 154, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 18, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 154, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 6},
    {.bitmap_index = 46, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 5, .ofs_y = -2},
    {.bitmap_index = 51, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 62, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 154, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 74, .adv_w = 154, .box_w = 2, .box_h = 2, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 84, .adv_w = 154, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 154, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 154, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 154, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 154, .box_w = 2, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 176, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 183, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 186, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 194, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 210, .adv_w = 154, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 154, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 375, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 466, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 475, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 480, .adv_w = 154, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 483, .adv_w = 154, .box_w = 10, .box_h = 1, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 485, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 487, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 547, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 154, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 575, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 626, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 636, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 699, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 710, .adv_w = 154, .box_w = 1, .box_h = 12, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 712, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 717, .adv_w = 154, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Courier_New_16 = {
#else
lv_font_t ui_font_Courier_New_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_COURIER_NEW_16*/

