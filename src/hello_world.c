#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "../lib/ssd1306/ssd1306.h"
#include "hardware/i2c.h"

#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

uint8_t buf[SSD1306_BUF_LEN];
struct render_area frame_area;

int main() {
    stdio_init_all();

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

    //R
    DrawLine(buf, 9, 54 >> 1, 17, 3 >> 1, 1);
    DrawLine(buf, 17, 3 >> 1, 35, 12 >> 1, 1);
    DrawLine(buf, 35, 12 >> 1, 13, 32 >> 1, 1);
    DrawLine(buf, 13, 32 >> 1, 31, 52 >> 1, 1);

    //H
    DrawLine(buf, 88, 10 >> 1, 82, 49 >> 1, 1);
    DrawLine(buf, 85, 29 >> 1, 111, 30 >> 1, 1);
    DrawLine(buf, 110, 12 >> 1, 108, 49 >> 1, 1);

    render(buf, &frame_area);

    while (1) {};
    return 0;
}
