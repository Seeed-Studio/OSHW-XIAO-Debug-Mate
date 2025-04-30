#include "LvglStyle.h"

lv_style_t style_screen;
lv_style_t style_uart_bg;
lv_style_t style_power_bg;
lv_style_t style_led;

lv_style_t style_font_18;
lv_style_t style_font_12;
lv_style_t style_font_14;
lv_style_t style_font_20;
lv_style_t style_font_22;
lv_style_t style_font_28;
lv_style_t style_font_32;
lv_style_t style_font_36;
lv_style_t style_font_40;

void initStyle() {
    lv_style_init(&style_screen);
    /* lv_style_set_bg_color(&style_screen, lv_color_hex(0xFFFFFF)); */
    lv_style_set_bg_color(&style_screen, lv_color_hex(0x000000));

    lv_style_init(&style_uart_bg);
    lv_style_set_bg_color(&style_uart_bg, lv_color_hex(0x232325));
    lv_style_set_radius(&style_uart_bg, 20);
    lv_style_set_border_width(&style_uart_bg, 2);
    lv_style_set_border_color(&style_uart_bg, lv_color_hex(0xACE62F));
    lv_style_set_border_opa(&style_uart_bg, LV_OPA_COVER); // 设置边框不透明度为完全不透明

    lv_style_init(&style_power_bg);
    lv_style_set_bg_color(&style_power_bg, lv_color_hex(0x232325));
    lv_style_set_radius(&style_power_bg, 20);

    lv_style_set_pad_all(&style_power_bg, 0);
    lv_style_set_border_width(&style_power_bg, 0);

    lv_style_init(&style_led);
    lv_style_set_width(&style_led, 10);
    lv_style_set_height(&style_led, 10);

    lv_style_init(&style_font_12);
    lv_style_set_text_font(&style_font_12, &lv_font_montserrat_12);

    lv_style_init(&style_font_14);
    lv_style_set_text_font(&style_font_14, &lv_font_montserrat_14);

    lv_style_init(&style_font_18);
    lv_style_set_text_font(&style_font_18, &lv_font_montserrat_18);

    lv_style_init(&style_font_20);
    lv_style_set_text_font(&style_font_20, &lv_font_montserrat_20);

    lv_style_init(&style_font_22);
    lv_style_set_text_font(&style_font_22, &lv_font_montserrat_22);

    lv_style_init(&style_font_28);
    lv_style_set_text_font(&style_font_28, &lv_font_montserrat_28);

    lv_style_init(&style_font_32);
    lv_style_set_text_font(&style_font_32, &lv_font_montserrat_32);

    lv_style_init(&style_font_36);
    lv_style_set_text_font(&style_font_36, &lv_font_montserrat_36);

    lv_style_init(&style_font_40);
    lv_style_set_text_font(&style_font_40, &lv_font_montserrat_40);
}
