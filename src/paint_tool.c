#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "../lib/display/draw.h"
#include "../lib/display/ssd1306_i2c.h"

#define _u(x) ((uint8_t)(x))

#define EB " "
#define UB "▀"
#define LB "▄"
#define FB "█"
#define CL "\x1b[H\x1b[2J"

uint8_t buf[SSD1306_BUF_LEN];

void render(uint8_t *buf);

int main()
{
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
    
    render(buf);

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

/*
 * Buf has the data for a 128 x 64 screen.
 * (Following interpretation assumes horizontal mode)
 *
 * This mimics to terminal the way SSD1306 ram is read.
 * It is split up in to 8 rows, one bit per pixel.
 * Each row is 128 long by 8 pixels high, each byte
 * Vertically arranged.
 *
 * byte 0 is x=0, y=0->7
 * byte 1 is x=1, y=0->7
 *
 * Every character in term is 2 bits, since we represent with
 * Full block, lower block and higher block.
 *
 * Function could be better but idc
*/

void render(uint8_t *buf)
{
  printf(CL);
  for (int row = 0; row < (SSD1306_HEIGHT / 2); row++) 
  {
    for (int ch = 0; ch < SSD1306_WIDTH; ch++)
    {
      uint8_t origin = buf[ch + SSD1306_WIDTH * (row / 4)];
      uint8_t mask = 0b00000011;
      uint8_t shift = 2 * (row % 4);
      uint8_t res = mask & origin >> shift;
      assert(res >= 0 && res < 4);
      switch (res)
      {
        case 0b00:
          printf(EB);
          break;
        case 0b01:
          printf(UB);
          break;
        case 0b10:
          printf(LB);
          break;
        case 0b11:
          printf(FB);
          break;
      }
    }
  printf("\n");
  }
}
