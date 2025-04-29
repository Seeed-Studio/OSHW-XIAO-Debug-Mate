#ifndef LVGL_STYLE_H
#define LVGL_STYLE_H

#include <lvgl.h>

extern lv_style_t style_screen;
extern lv_style_t style_uart_bg;
extern lv_style_t style_power_bg;
extern lv_style_t style_led;

extern lv_style_t style_font_18;
extern lv_style_t style_font_12;
extern lv_style_t style_font_14;
extern lv_style_t style_font_20;
extern lv_style_t style_font_22;
extern lv_style_t style_font_28;

void initStyle();

#endif
