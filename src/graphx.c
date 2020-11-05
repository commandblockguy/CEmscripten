#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "graphx.h"

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

uint16_t gfx_palette[256] = {0x0000, 0x0081, 0x0102, 0x0183, 0x0204, 0x0285, 0x0306, 0x0387, 0x0408, 0x0489, 0x050a, 0x058b, 0x060c, 0x068d, 0x070e, 0x078f, 0x0810, 0x0891, 0x0912, 0x0993, 0x0a14, 0x0a95, 0x0b16, 0x0b97, 0x0c18, 0x0c99, 0x0d1a, 0x0d9b, 0x0e1c, 0x0e9d, 0x0f1e, 0x0f9f, 0x9000, 0x9081, 0x9102, 0x9183, 0x9204, 0x9285, 0x9306, 0x9387, 0x9408, 0x9489, 0x950a, 0x958b, 0x960c, 0x968d, 0x970e, 0x978f, 0x9810, 0x9891, 0x9912, 0x9993, 0x9a14, 0x9a95, 0x9b16, 0x9b97, 0x9c18, 0x9c99, 0x9d1a, 0x9d9b, 0x9e1c, 0x9e9d, 0x9f1e, 0x9f9f, 0x2020, 0x20a1, 0x2122, 0x21a3, 0x2224, 0x22a5, 0x2326, 0x23a7, 0x2428, 0x24a9, 0x252a, 0x25ab, 0x262c, 0x26ad, 0x272e, 0x27af, 0x2830, 0x28b1, 0x2932, 0x29b3, 0x2a34, 0x2ab5, 0x2b36, 0x2bb7, 0x2c38, 0x2cb9, 0x2d3a, 0x2dbb, 0x2e3c, 0x2ebd, 0x2f3e, 0x2fbf, 0xb020, 0xb0a1, 0xb122, 0xb1a3, 0xb224, 0xb2a5, 0xb326, 0xb3a7, 0xb428, 0xb4a9, 0xb52a, 0xb5ab, 0xb62c, 0xb6ad, 0xb72e, 0xb7af, 0xb830, 0xb8b1, 0xb932, 0xb9b3, 0xba34, 0xbab5, 0xbb36, 0xbbb7, 0xbc38, 0xbcb9, 0xbd3a, 0xbdbb, 0xbe3c, 0xbebd, 0xbf3e, 0xbfbf, 0x4040, 0x40c1, 0x4142, 0x41c3, 0x4244, 0x42c5, 0x4346, 0x43c7, 0x4448, 0x44c9, 0x454a, 0x45cb, 0x464c, 0x46cd, 0x474e, 0x47cf, 0x4850, 0x48d1, 0x4952, 0x49d3, 0x4a54, 0x4ad5, 0x4b56, 0x4bd7, 0x4c58, 0x4cd9, 0x4d5a, 0x4ddb, 0x4e5c, 0x4edd, 0x4f5e, 0x4fdf, 0xd040, 0xd0c1, 0xd142, 0xd1c3, 0xd244, 0xd2c5, 0xd346, 0xd3c7, 0xd448, 0xd4c9, 0xd54a, 0xd5cb, 0xd64c, 0xd6cd, 0xd74e, 0xd7cf, 0xd850, 0xd8d1, 0xd952, 0xd9d3, 0xda54, 0xdad5, 0xdb56, 0xdbd7, 0xdc58, 0xdcd9, 0xdd5a, 0xdddb, 0xde5c, 0xdedd, 0xdf5e, 0xdfdf, 0x6060, 0x60e1, 0x6162, 0x61e3, 0x6264, 0x62e5, 0x6366, 0x63e7, 0x6468, 0x64e9, 0x656a, 0x65eb, 0x666c, 0x66ed, 0x676e, 0x67ef, 0x6870, 0x68f1, 0x6972, 0x69f3, 0x6a74, 0x6af5, 0x6b76, 0x6bf7, 0x6c78, 0x6cf9, 0x6d7a, 0x6dfb, 0x6e7c, 0x6efd, 0x6f7e, 0x6fff, 0xf060, 0xf0e1, 0xf162, 0xf1e3, 0xf264, 0xf2e5, 0xf366, 0xf3e7, 0xf468, 0xf4e9, 0xf56a, 0xf5eb, 0xf66c, 0xf6ed, 0xf76e, 0xf7ef, 0xf870, 0xf8f1, 0xf972, 0xf9f3, 0xfa74, 0xfaf5, 0xfb76, 0xfbf7, 0xfc78, 0xfcf9, 0xfd7a, 0xfdfb, 0xfe7c, 0xfefd, 0xff7e, 0xffff, };
uint8_t gfx_vram[LCD_WIDTH*LCD_HEIGHT*2];

static gfx_location_t draw_location = gfx_screen;
static bool screen_swapped = false;
static uint8_t color = 0;
static uint8_t transparent_color = 0;
static uint8_t text_fg_color = 0;
static uint8_t text_bg_color = 0;
static uint8_t text_transparent_color = 0;
static int text_x = 0;
static int text_y = 0;

uint8_t spacings[256] = {
    8,8,8,8,8,8,8,8,8,8,8,8,8,2,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    3,4,6,8,8,8,8,5,5,5,8,7,4,7,3,8,
    8,7,8,8,8,8,8,8,8,8,3,4,6,7,6,7,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,5,8,5,8,8,
    4,8,8,8,8,8,8,8,8,5,8,8,5,8,8,8,
    8,8,8,8,7,8,8,8,8,8,8,7,3,7,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};
uint8_t font[256][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // .
    {0x7E,0x81,0xA5,0x81,0xBD,0xBD,0x81,0x7E}, // .
    {0x7E,0xFF,0xDB,0xFF,0xC3,0xC3,0xFF,0x7E}, // .
    {0x6C,0xFE,0xFE,0xFE,0x7C,0x38,0x10,0x00}, // .
    {0x10,0x38,0x7C,0xFE,0x7C,0x38,0x10,0x00}, // .
    {0x38,0x7C,0x38,0xFE,0xFE,0x10,0x10,0x7C}, // .
    {0x00,0x18,0x3C,0x7E,0xFF,0x7E,0x18,0x7E}, // .
    {0x00,0x00,0x18,0x3C,0x3C,0x18,0x00,0x00}, // .
    {0xFF,0xFF,0xE7,0xC3,0xC3,0xE7,0xFF,0xFF}, // .
    {0x00,0x3C,0x66,0x42,0x42,0x66,0x3C,0x00}, // .
    {0xFF,0xC3,0x99,0xBD,0xBD,0x99,0xC3,0xFF}, // .
    {0x0F,0x07,0x0F,0x7D,0xCC,0xCC,0xCC,0x78}, // .
    {0x3C,0x66,0x66,0x66,0x3C,0x18,0x7E,0x18}, // .
    {0x3F,0x33,0x3F,0x30,0x30,0x70,0xF0,0xE0}, // .
    {0x7F,0x63,0x7F,0x63,0x63,0x67,0xE6,0xC0}, // .
    {0x99,0x5A,0x3C,0xE7,0xE7,0x3C,0x5A,0x99}, // .
    {0x80,0xE0,0xF8,0xFE,0xF8,0xE0,0x80,0x00}, // .
    {0x02,0x0E,0x3E,0xFE,0x3E,0x0E,0x02,0x00}, // .
    {0x18,0x3C,0x7E,0x18,0x18,0x7E,0x3C,0x18}, // .
    {0x66,0x66,0x66,0x66,0x66,0x00,0x66,0x00}, // .
    {0x7F,0xDB,0xDB,0x7B,0x1B,0x1B,0x1B,0x00}, // .
    {0x3F,0x60,0x7C,0x66,0x66,0x3E,0x06,0xFC}, // .
    {0x00,0x00,0x00,0x00,0x7E,0x7E,0x7E,0x00}, // .
    {0x18,0x3C,0x7E,0x18,0x7E,0x3C,0x18,0xFF}, // .
    {0x18,0x3C,0x7E,0x18,0x18,0x18,0x18,0x00}, // .
    {0x18,0x18,0x18,0x18,0x7E,0x3C,0x18,0x00}, // .
    {0x00,0x18,0x0C,0xFE,0x0C,0x18,0x00,0x00}, // .
    {0x00,0x30,0x60,0xFE,0x60,0x30,0x00,0x00}, // .
    {0x00,0x00,0xC0,0xC0,0xC0,0xFE,0x00,0x00}, // .
    {0x00,0x24,0x66,0xFF,0x66,0x24,0x00,0x00}, // .
    {0x00,0x18,0x3C,0x7E,0xFF,0xFF,0x00,0x00}, // .
    {0x00,0xFF,0xFF,0x7E,0x3C,0x18,0x00,0x00}, // .
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //
    {0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0xC0,0x00}, // !
    {0xD8,0xD8,0xD8,0x00,0x00,0x00,0x00,0x00}, // "
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00}, // #
    {0x18,0x7E,0xC0,0x7C,0x06,0xFC,0x18,0x00}, // $
    {0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00}, // %
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00}, // &
    {0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00}, // '
    {0x30,0x60,0xC0,0xC0,0xC0,0x60,0x30,0x00}, // (
    {0xC0,0x60,0x30,0x30,0x30,0x60,0xC0,0x00}, // )
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, // *
    {0x00,0x30,0x30,0xFC,0xFC,0x30,0x30,0x00}, // +
    {0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xC0}, // ,
    {0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00}, // -
    {0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00}, // .
    {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00}, // /
    {0x7C,0xCE,0xDE,0xF6,0xE6,0xC6,0x7C,0x00}, // 0
    {0x30,0x70,0x30,0x30,0x30,0x30,0xFC,0x00}, // 1
    {0x7C,0xC6,0x06,0x7C,0xC0,0xC0,0xFE,0x00}, // 2
    {0xFC,0x06,0x06,0x3C,0x06,0x06,0xFC,0x00}, // 3
    {0x0C,0xCC,0xCC,0xCC,0xFE,0x0C,0x0C,0x00}, // 4
    {0xFE,0xC0,0xFC,0x06,0x06,0xC6,0x7C,0x00}, // 5
    {0x7C,0xC0,0xC0,0xFC,0xC6,0xC6,0x7C,0x00}, // 6
    {0xFE,0x06,0x06,0x0C,0x18,0x30,0x30,0x00}, // 7
    {0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00}, // 8
    {0x7C,0xC6,0xC6,0x7E,0x06,0x06,0x7C,0x00}, // 9
    {0x00,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0x00}, // :
    {0x00,0x60,0x60,0x00,0x00,0x60,0x60,0xC0}, // ;
    {0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x00}, // <
    {0x00,0x00,0xFC,0x00,0xFC,0x00,0x00,0x00}, // =
    {0xC0,0x60,0x30,0x18,0x30,0x60,0xC0,0x00}, // >
    {0x78,0xCC,0x18,0x30,0x30,0x00,0x30,0x00}, // ?
    {0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x7E,0x00}, // @
    {0x38,0x6C,0xC6,0xC6,0xFE,0xC6,0xC6,0x00}, // A
    {0xFC,0xC6,0xC6,0xFC,0xC6,0xC6,0xFC,0x00}, // B
    {0x7C,0xC6,0xC0,0xC0,0xC0,0xC6,0x7C,0x00}, // C
    {0xF8,0xCC,0xC6,0xC6,0xC6,0xCC,0xF8,0x00}, // D
    {0xFE,0xC0,0xC0,0xF8,0xC0,0xC0,0xFE,0x00}, // E
    {0xFE,0xC0,0xC0,0xF8,0xC0,0xC0,0xC0,0x00}, // F
    {0x7C,0xC6,0xC0,0xC0,0xCE,0xC6,0x7C,0x00}, // G
    {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, // H
    {0x7E,0x18,0x18,0x18,0x18,0x18,0x7E,0x00}, // I
    {0x06,0x06,0x06,0x06,0x06,0xC6,0x7C,0x00}, // J
    {0xC6,0xCC,0xD8,0xF0,0xD8,0xCC,0xC6,0x00}, // K
    {0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0x00}, // L
    {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00}, // M
    {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00}, // N
    {0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00}, // O
    {0xFC,0xC6,0xC6,0xFC,0xC0,0xC0,0xC0,0x00}, // P
    {0x7C,0xC6,0xC6,0xC6,0xD6,0xDE,0x7C,0x06}, // Q
    {0xFC,0xC6,0xC6,0xFC,0xD8,0xCC,0xC6,0x00}, // R
    {0x7C,0xC6,0xC0,0x7C,0x06,0xC6,0x7C,0x00}, // S
    {0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x00}, // T
    {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xFE,0x00}, // U
    {0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x38,0x00}, // V
    {0xC6,0xC6,0xC6,0xC6,0xD6,0xFE,0x6C,0x00}, // W
    {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00}, // X
    {0xC6,0xC6,0xC6,0x7C,0x18,0x30,0xE0,0x00}, // Y
    {0xFE,0x06,0x0C,0x18,0x30,0x60,0xFE,0x00}, // Z
    {0xF0,0xC0,0xC0,0xC0,0xC0,0xC0,0xF0,0x00}, // [
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00}, // (backslash)
    {0xF0,0x30,0x30,0x30,0x30,0x30,0xF0,0x00}, // ]
    {0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00}, // ^
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF}, // _
    {0xC0,0xC0,0x60,0x00,0x00,0x00,0x00,0x00}, // `
    {0x00,0x00,0x7C,0x06,0x7E,0xC6,0x7E,0x00}, // a
    {0xC0,0xC0,0xC0,0xFC,0xC6,0xC6,0xFC,0x00}, // b
    {0x00,0x00,0x7C,0xC6,0xC0,0xC6,0x7C,0x00}, // c
    {0x06,0x06,0x06,0x7E,0xC6,0xC6,0x7E,0x00}, // d
    {0x00,0x00,0x7C,0xC6,0xFE,0xC0,0x7C,0x00}, // e
    {0x1C,0x36,0x30,0x78,0x30,0x30,0x78,0x00}, // f
    {0x00,0x00,0x7E,0xC6,0xC6,0x7E,0x06,0xFC}, // g
    {0xC0,0xC0,0xFC,0xC6,0xC6,0xC6,0xC6,0x00}, // h
    {0x60,0x00,0xE0,0x60,0x60,0x60,0xF0,0x00}, // i
    {0x06,0x00,0x06,0x06,0x06,0x06,0xC6,0x7C}, // j
    {0xC0,0xC0,0xCC,0xD8,0xF8,0xCC,0xC6,0x00}, // k
    {0xE0,0x60,0x60,0x60,0x60,0x60,0xF0,0x00}, // l
    {0x00,0x00,0xCC,0xFE,0xFE,0xD6,0xD6,0x00}, // m
    {0x00,0x00,0xFC,0xC6,0xC6,0xC6,0xC6,0x00}, // n
    {0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00}, // o
    {0x00,0x00,0xFC,0xC6,0xC6,0xFC,0xC0,0xC0}, // p
    {0x00,0x00,0x7E,0xC6,0xC6,0x7E,0x06,0x06}, // q
    {0x00,0x00,0xFC,0xC6,0xC0,0xC0,0xC0,0x00}, // r
    {0x00,0x00,0x7E,0xC0,0x7C,0x06,0xFC,0x00}, // s
    {0x30,0x30,0xFC,0x30,0x30,0x30,0x1C,0x00}, // t
    {0x00,0x00,0xC6,0xC6,0xC6,0xC6,0x7E,0x00}, // u
    {0x00,0x00,0xC6,0xC6,0xC6,0x7C,0x38,0x00}, // v
    {0x00,0x00,0xC6,0xC6,0xD6,0xFE,0x6C,0x00}, // w
    {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00}, // x
    {0x00,0x00,0xC6,0xC6,0xC6,0x7E,0x06,0xFC}, // y
    {0x00,0x00,0xFE,0x0C,0x38,0x60,0xFE,0x00}, // z
    {0x1C,0x30,0x30,0xE0,0x30,0x30,0x1C,0x00}, // {
    {0xC0,0xC0,0xC0,0x00,0xC0,0xC0,0xC0,0x00}, // |
    {0xE0,0x30,0x30,0x1C,0x30,0x30,0xE0,0x00}, // }
    {0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00}, // ~
    {0x00,0x10,0x38,0x6C,0xC6,0xC6,0xFE,0x00}, // .
};

uint16_t *graphx_get_palette(void) {
	return gfx_palette;
}

uint8_t *graphx_get_vram(void) {
	return &gfx_vram[screen_swapped ? LCD_WIDTH * LCD_HEIGHT : 0];
}

uint8_t *gfx_GetVBuffer(void) {
	return &gfx_vram[(draw_location ^ screen_swapped) ? LCD_WIDTH * LCD_HEIGHT : 0];
}

uint8_t *gfx_GetFBuffer(void) {
	return &gfx_vram[screen_swapped ? LCD_WIDTH * LCD_HEIGHT : 0];
}

uint8_t *gfx_GetBBuffer(void) {
	return &gfx_vram[screen_swapped ? 0 : LCD_WIDTH * LCD_HEIGHT];
}

void gfx_SetDraw(uint8_t location) {
	draw_location = location;
}

void gfx_FillScreen(uint8_t index) {
	memset(gfx_GetVBuffer(), index, LCD_WIDTH*LCD_HEIGHT);
}

void gfx_SetPalette(void *palette, unsigned int size, uint8_t offset) {
	memcpy(&gfx_palette[offset], palette, size);
}

uint8_t gfx_SetColor(uint8_t index) {
	uint8_t old = color;
	color = index;
	return old;
}

void gfx_Blit(gfx_location_t src) {
	if(src == gfx_screen) {
		memcpy(gfx_GetBBuffer(), gfx_GetFBuffer(), LCD_WIDTH*LCD_HEIGHT);
	} else {
		memcpy(gfx_GetFBuffer(), gfx_GetBBuffer(), LCD_WIDTH*LCD_HEIGHT);
	}
}

void gfx_FillRectangle(int x,
                       int y,
                       int width,
                       int height) {
	uint8_t *current_out = gfx_GetVBuffer() + x + LCD_WIDTH * y;
	uint8_t index = color;
	for(int y = 0; y < height; y++) {
		memset(current_out, index, width);
		current_out += LCD_WIDTH;
	}
}

void gfx_Sprite(gfx_sprite_t *sprite, int x, int y) {
	uint8_t *current_in = sprite->data;
	uint8_t *current_out = gfx_GetVBuffer() + x + LCD_WIDTH * y;
	for(int sprite_y = 0; sprite_y < sprite->height; sprite_y++) {
		memcpy(current_out, current_in, sprite->width);
		current_in += sprite->width;
		current_out += LCD_WIDTH;
	}
}

void gfx_TransparentSprite(gfx_sprite_t *sprite, int x, int y) {
	uint8_t *current_in = sprite->data;
	uint8_t *current_out = gfx_GetVBuffer() + x + LCD_WIDTH * y;
	uint8_t transparent_color = transparent_color;
	for(int sprite_y = 0; sprite_y < sprite->height; sprite_y++) {
		for(int sprite_x = 0; sprite_x < sprite->width; sprite_x++) {
			if(*current_in != transparent_color) {
				*current_out = *current_in;
			}
			current_in++;
			current_out++;
		}
		current_out += LCD_WIDTH - sprite->width;
	}
}

gfx_sprite_t *gfx_GetSprite(gfx_sprite_t *sprite, int x, int y) {
	uint8_t *current_out = sprite->data;
	uint8_t *current_in = gfx_GetVBuffer() + x + LCD_WIDTH * y;
	for(int sprite_y = 0; sprite_y < sprite->height; sprite_y++) {
		memcpy(current_out, current_in, sprite->width);
		current_out += sprite->width;
		current_in += LCD_WIDTH;
	}
	return sprite;
}

gfx_sprite_t *gfx_FlipSpriteY(gfx_sprite_t *sprite_in,
                              gfx_sprite_t *sprite_out) {
	sprite_out->width = sprite_in->width;
	sprite_out->height = sprite_in->height;
	for(int y = 0; y < sprite_in->height; y++) {
		for(int x = 0; x < sprite_in->width; x++) {
			sprite_out->data[x + y * sprite_in->width] = sprite_in->data[sprite_in->width - 1 - x + y * sprite_in->width];
		}
	}
	return sprite_out;
}

gfx_sprite_t *gfx_RotateSpriteC(gfx_sprite_t *sprite_in,
                                gfx_sprite_t *sprite_out) {
	sprite_out->width = sprite_in->height;
	sprite_out->height = sprite_in->width;
	for(int y = 0; y < sprite_in->height; y++) {
		for(int x = 0; x < sprite_in->width; x++) {
			// todo: something needs to be flipped
			sprite_out->data[x * sprite_out->width + y] = sprite_in->data[x + y * sprite_in->width];
		}
	}
	return sprite_out;
}

uint8_t gfx_SetTextFGColor(uint8_t color) {
	uint8_t old = text_fg_color;
	text_fg_color = color;
	return old;
}

void gfx_PrintChar(char c) {
    int width = spacings[c];
    for(int y = 0; y < 8; y++) {
        int row = font[c][y];
        for(int x = 0; x < width; x++) {
            if(row & (1 << (7 - x))) gfx_GetVBuffer()[text_x + x + LCD_WIDTH * (text_y + y)] = text_fg_color;
        }
    }
    text_x += width;
}

void gfx_PrintString(const char *string) {
	for(int i = 0; i < strlen(string); i++) {
		gfx_PrintChar(string[i]);
	}
}

void gfx_PrintStringXY(const char *string, int x, int y) {
	gfx_SetTextXY(x, y);
	gfx_PrintString(string);
}

void gfx_SetTextXY(int x, int y) {
	text_x = x;
	text_y = y;
}

void gfx_PrintUInt(unsigned int n, uint8_t length) {
	char buf[32];
	snprintf(buf, sizeof buf, "%.*u", length, n);
	gfx_PrintString(buf);
}