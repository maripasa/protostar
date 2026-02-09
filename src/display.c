#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/display/ssd1306.h"
#include "../lib/display/draw.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

struct render_area frame_area;
uint8_t buf[SSD1306_BUF_LEN];

void ssd1306_init_display(void)
{
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    
    SSD1306_init();
    frame_area.start_col  = 0;
    frame_area.end_col    = SSD1306_WIDTH - 1;
    frame_area.start_page = 0;
    frame_area.end_page   = SSD1306_NUM_PAGES - 1;
    calc_render_area_buflen(&frame_area);
    memset(buf, 0, SSD1306_BUF_LEN);
}

int main() {
    stdio_init_all();
    ssd1306_init_display();

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



    render(buf, &frame_area);

    while (1) {};
    return 0;
}
