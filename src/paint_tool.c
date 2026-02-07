#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
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
    return 0;
}
