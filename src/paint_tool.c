// I just want to use the blocks man... Want to bet it would be less strange to bleed to a window?... nah
#define _XOPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ncurses.h>
#include <wchar.h>

#include "../lib/display/draw.h"
#include "../lib/display/ssd1306_i2c.h"

#define EMPTY_BLOCK L' '
#define UPPER_BLOCK L'▀'
#define LOWER_BLOCK L'▄'
#define FULL_BLOCK L'█'

uint8_t display_buffer[SSD1306_BUF_LEN];

double last_frame_time;
double last_fps_update;

void render2terminal(uint8_t *display_buffer);

static double now_seconds(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

int main() {
  setlocale(LC_ALL, ""); // Unicode for blocks
  initscr(); // Start curses mode
  nodelay(stdscr, TRUE); // Non-blocking input
  cbreak(); // Line buffering disabled
  noecho();
  keypad(stdscr, TRUE); // Special keys
  curs_set(0); // Hide cursor
  scrollok(stdscr, FALSE); // No scrolling

  last_frame_time = now_seconds();
  last_fps_update = last_frame_time;
  char fps_number[16] = "0";
  char key_str[16] = "0";

  int ch;
  int frames = 0;

  while (1) {
    memset(display_buffer, 0, SSD1306_BUF_LEN);


    // Input
    ch = getch();
    if (ch != ERR) {
      snprintf(key_str, sizeof(key_str), "%c %d", ch, ch);
    }
    write_string(display_buffer, 0, 9, key_str);

    double current_time = now_seconds();
    //double delta = current_time - last_frame_time;
    frames++;

    // Show FPS every 0.5s
    double delta_fps_update = current_time - last_fps_update;
    if (delta_fps_update > 0.5) {
      float fps = frames / delta_fps_update;
      snprintf(fps_number, sizeof(fps_number), "%.0f", fps);
      frames = 0;
      last_fps_update = current_time;
    }

    write_string(display_buffer, 0, 0, fps_number);
    draw_texture(display_buffer, 20, 20, BRUSH, false, true);

    last_frame_time = current_time;

    render2terminal(display_buffer);
  }

  endwin(); // End curses mode
  return 0;
}

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
void render2terminal(uint8_t *display_buffer) {
  for (int row = 0; row < SSD1306_HEIGHT / 2; row++) {
    wchar_t line[SSD1306_WIDTH + 1]; // +1 null

    for (int col = 0; col < SSD1306_WIDTH; col++) {
      uint8_t byte = display_buffer[col + SSD1306_WIDTH * (row / 4)];
      uint8_t mask = 0b00000011;
      uint8_t shift = 2 * (row % 4);
      uint8_t val = (byte >> shift) & mask;

      switch (val) {
        case 0b00: line[col] = EMPTY_BLOCK; break;
        case 0b01: line[col] = UPPER_BLOCK; break;
        case 0b10: line[col] = LOWER_BLOCK; break;
        case 0b11: line[col] = FULL_BLOCK; break;
      }
    }
    line[SSD1306_WIDTH] = L'\0';

    mvaddwstr(row, 0, line);
  }
  refresh();
}
