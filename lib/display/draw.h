// I could be wrong, but for now there won't be images bigger than 8x8
#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>
#include "textures.h"


extern void set_pixel(uint8_t *buf, int x, int y, bool on);
extern void draw_line(uint8_t *buf, int x0, int y0, int x1, int y1, bool on);
extern void write_char(uint8_t *buf, int16_t x, int16_t y, uint8_t ch);
extern void write_string(uint8_t *buf, int16_t x, int16_t y, char *str);
extern void draw_texture(uint8_t *buf, int x, int y, Texture img, bool inverted, bool alpha);

#endif // DRAW_H_
