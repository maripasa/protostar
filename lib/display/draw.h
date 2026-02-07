extern void set_pixel(uint8_t *buf, int x, int y, bool on);
extern void draw_line(uint8_t *buf, int x0, int y0, int x1, int y1, bool on);
extern void write_char(uint8_t *buf, int16_t x, int16_t y, uint8_t ch);
extern void write_string(uint8_t *buf, int16_t x, int16_t y, char *str);
