#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../lib/draw/fonts.h"
#include "../lib/draw/draw.h"
#include "../lib/draw/ssd1306_i2c.h"

#define _u(x) ((uint8_t)(x))

#define UB "▀"
#define LB "▄"
#define FB "█"
#define CL "\x1b[H\x1b[2J"

uint8_t buf[SSD1306_BUF_LEN];

int main() {
    printf("%s", CL);
    //R
    draw_line(buf, 9, 54, 17, 3, 1);
    draw_line(buf, 17, 3, 35, 12, 1);
    draw_line(buf, 35, 12, 13, 32, 1);
    draw_line(buf, 13, 32, 31, 52, 1);

    //H
    draw_line(buf, 88, 10, 82, 49, 1);
    draw_line(buf, 85, 29, 111, 30, 1);
    draw_line(buf, 110, 12, 108, 49, 1);
    
    // The line
    draw_line(buf, 9, 34, 111, 36, 1);
    return 0;
}

/*
frame_area.start_col  = 0;
frame_area.end_col    = SSD1306_WIDTH - 1;
frame_area.start_page = 0;
frame_area.end_page   = SSD1306_NUM_PAGES - 1;
calc_render_area_buflen(&frame_area);
memset(buf, 0, SSD1306_BUF_LEN);
render(buf, &frame_area);
*/

void render(uint8_t *buf){
  ;
}
