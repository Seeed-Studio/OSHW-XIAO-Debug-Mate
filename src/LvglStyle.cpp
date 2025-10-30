#include "LvglStyle.h"

lv_style_t style_screen;
lv_style_t style_rxtx_bg;
lv_style_t style_focus_bg;
lv_style_t style_focus_uart_bg;
lv_style_t style_nofocus_bg;
lv_style_t style_nofocus_uart_bg;
lv_style_t style_led;
lv_style_t style_uart_line;
lv_style_t style_focus_uart_line;

lv_style_t style_font_18;
lv_style_t style_font_12;
lv_style_t style_font_14;
lv_style_t style_font_16;
lv_style_t style_font_20;
lv_style_t style_font_22;
lv_style_t style_font_26;
lv_style_t style_font_28;
lv_style_t style_font_32;
lv_style_t style_font_30;
lv_style_t style_font_36;
lv_style_t style_font_48;

void initStyle() {
    lv_style_init(&style_screen);
    /* lv_style_set_bg_color(&style_screen, lv_color_hex(0xFFFFFF)); */
    lv_style_set_bg_color(&style_screen, lv_color_hex(0x000000));
    lv_style_set_pad_all(&style_screen, 0);
    lv_style_set_border_width(&style_screen, 0);

    lv_style_init(&style_rxtx_bg);
    lv_style_set_bg_color(&style_rxtx_bg, lv_color_hex(0x232325));
    lv_style_set_pad_all(&style_rxtx_bg, 0);
    lv_style_set_pad_top(&style_rxtx_bg, 10);
    lv_style_set_border_width(&style_rxtx_bg, 0);

    lv_style_init(&style_focus_bg);
    lv_style_set_bg_color(&style_focus_bg, lv_color_hex(0x232325));
    lv_style_set_radius(&style_focus_bg, 20);
    lv_style_set_pad_all(&style_focus_bg, 0);
    lv_style_set_border_width(&style_focus_bg, 2);
    lv_style_set_border_color(&style_focus_bg, lv_color_hex(0xACE62F));
    lv_style_set_border_opa(&style_focus_bg, LV_OPA_COVER); // Set border opacity to fully opaque

    lv_style_init(&style_focus_uart_bg);
    lv_style_set_bg_color(&style_focus_uart_bg, lv_color_hex(0x232325));
    lv_style_set_radius(&style_focus_uart_bg, 90);
    lv_style_set_pad_all(&style_focus_uart_bg, 0);
    lv_style_set_border_width(&style_focus_uart_bg, 2);
    lv_style_set_border_color(&style_focus_uart_bg, lv_color_hex(0xACE62F));
    lv_style_set_border_opa(&style_focus_uart_bg, LV_OPA_COVER); // Set border opacity to fully opaque

    lv_style_init(&style_nofocus_bg);
    lv_style_set_bg_color(&style_nofocus_bg, lv_color_hex(0x232325));
    lv_style_set_radius(&style_nofocus_bg, 20);
    lv_style_set_pad_all(&style_nofocus_bg, 0);
    lv_style_set_border_width(&style_nofocus_bg, 2);
    lv_style_set_border_color(&style_nofocus_bg, lv_color_hex(0x000000));

    lv_style_init(&style_nofocus_uart_bg);
    lv_style_set_bg_color(&style_nofocus_uart_bg, lv_color_hex(0x232325));
    lv_style_set_radius(&style_nofocus_uart_bg, 90);
    lv_style_set_pad_all(&style_nofocus_uart_bg, 0);
    lv_style_set_border_width(&style_nofocus_uart_bg, 2);
    lv_style_set_border_color(&style_nofocus_uart_bg, lv_color_hex(0x000000));

    lv_style_init(&style_led);
    lv_style_set_size(&style_led, 10, 10);
    lv_style_set_shadow_width(&style_led, 0);
    lv_style_set_shadow_spread(&style_led, 0);
    lv_style_set_border_width(&style_led, 0);

    lv_style_init(&style_uart_line);
    lv_style_set_line_color(&style_uart_line, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_width(&style_uart_line, 2);
    lv_style_set_line_rounded(&style_uart_line, true);

    lv_style_init(&style_focus_uart_line);
    lv_style_set_line_color(&style_focus_uart_line, lv_color_hex(0xACE62F));
    lv_style_set_line_width(&style_focus_uart_line, 2);
    lv_style_set_line_rounded(&style_focus_uart_line, true);

    lv_style_init(&style_font_12);
    lv_style_set_text_font(&style_font_12, &lv_font_montserrat_12);

    lv_style_init(&style_font_14);
    lv_style_set_text_font(&style_font_14, &lv_font_montserrat_14);

    lv_style_init(&style_font_16);
    lv_style_set_text_font(&style_font_16, &lv_font_montserrat_16);

    lv_style_init(&style_font_18);
    lv_style_set_text_font(&style_font_18, &lv_font_montserrat_18);

    lv_style_init(&style_font_20);
    lv_style_set_text_font(&style_font_20, &lv_font_montserrat_20);

    lv_style_init(&style_font_22);
    lv_style_set_text_font(&style_font_22, &lv_font_montserrat_22);

    lv_style_init(&style_font_26);
    lv_style_set_text_font(&style_font_26, &lv_font_montserrat_26);

    lv_style_init(&style_font_28);
    lv_style_set_text_font(&style_font_28, &lv_font_montserrat_28);

    lv_style_init(&style_font_30);
    lv_style_set_text_font(&style_font_30, &lv_font_montserrat_30);

    lv_style_init(&style_font_32);
    lv_style_set_text_font(&style_font_32, &lv_font_montserrat_32);

    lv_style_init(&style_font_36);
    lv_style_set_text_font(&style_font_36, &lv_font_montserrat_36);

    lv_style_init(&style_font_48);
    lv_style_set_text_font(&style_font_48, &lv_font_montserrat_48);
}
