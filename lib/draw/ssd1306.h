#include "ssd1306_i2c.h"
extern void calc_render_area_buflen(struct render_area *area);
extern void SSD1306_send_cmd(uint8_t cmd);
extern void SSD1306_send_cmd_list(uint8_t *buf, int num);
extern void SSD1306_send_buf(uint8_t buf[], int buflen);
extern void SSD1306_init();
extern void SSD1306_scroll(bool on);
extern void render(uint8_t *buf, struct render_area *area);
