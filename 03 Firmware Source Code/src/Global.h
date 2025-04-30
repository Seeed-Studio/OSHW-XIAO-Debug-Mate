#ifndef GLOBAL_H
#define GLOBAL_H

#define BOOT_BTN 1

/*Set to your screen resolution and rotation*/
#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_270
#define LABEL_BUFFER_SIZE 16

#define DEBOUNCE_DELAT 50 // 消抖延迟，单位毫秒
#define LONG_PRESS_DELAY 1000 // 长按延迟，单位毫秒

#define LOGI(format, ...) Serial.printf("[INFO] "  "%s::%d" "  \"" format "\"  " "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGE(format, ...) Serial.printf("[ERROR] " "%s::%d" "  \"" format "\"  " "\n", __FILE__, __LINE__, ##__VA_ARGS__)


extern unsigned long startTime;

#endif
