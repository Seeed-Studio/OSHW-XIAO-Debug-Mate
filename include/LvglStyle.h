#ifndef LVGL_STYLE_H
#define LVGL_STYLE_H

#include <lvgl.h>

extern lv_style_t style_screen;
extern lv_style_t style_rxtx_bg;
extern lv_style_t style_focus_bg;
extern lv_style_t style_focus_uart_bg;
extern lv_style_t style_nofocus_bg;
extern lv_style_t style_nofocus_uart_bg;
extern lv_style_t style_led;
extern lv_style_t style_uart_line;
extern lv_style_t style_focus_uart_line;

extern lv_style_t style_font_18;
extern lv_style_t style_font_12;
extern lv_style_t style_font_14;
extern lv_style_t style_font_16;
extern lv_style_t style_font_20;
extern lv_style_t style_font_22;
extern lv_style_t style_font_26;
extern lv_style_t style_font_28;
extern lv_style_t style_font_30;
extern lv_style_t style_font_32;
extern lv_style_t style_font_36;
extern lv_style_t style_font_48;


void initStyle();

#endif
