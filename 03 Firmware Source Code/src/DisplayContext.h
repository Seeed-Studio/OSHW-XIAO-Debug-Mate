#ifndef DISPLAY_CONTEXT_H
#define DISPLAY_CONTEXT_H

#include "FreeRTOS.h"
#include "semphr.h"

#include <TFT_eSPI.h>
#include <SPI.h>
#include "Free_Fonts.h"

// 显示上下文，提供绘图API
class DisplayContext {
private:
    SemaphoreHandle_t m_displayMutex;
    TFT_eSPI* m_tft;
    
public:
    DisplayContext() {
        m_displayMutex = xSemaphoreCreateMutex();
        m_tft = nullptr;
    }
    
    ~DisplayContext() {
        if (m_displayMutex) {
            vSemaphoreDelete(m_displayMutex);
        }
    }

    void setTft(TFT_eSPI* tft) {
        m_tft = tft;
    }
    
    // 获取显示锁
    bool lock(TickType_t timeout = portMAX_DELAY) {
        return (xSemaphoreTake(m_displayMutex, timeout) == pdTRUE);
    }
    
    // 释放显示锁
    void unlock() {
        xSemaphoreGive(m_displayMutex);
    }
    
    // 清除屏幕
    void clear() {
        // 实现清屏功能
    }
    
    // 绘制文本
    void drawText(int x, int y, const char* text, bool isBold = false) {
        // 实现文本绘制
    }
    
    // 绘制矩形
    void drawRect(int x, int y, int width, int height, bool fill = false) {
        // 实现矩形绘制
    }
    
    // 绘制图像
    void drawImage(int x, int y, const uint8_t* imageData, int width, int height) {
        // 实现图像绘制
    }

    void drawText() {
        m_tft->fillScreen(TFT_GREEN);
    }

    void drawRect() {
        m_tft->fillScreen(TFT_BLUE);
    }

    void drawImage() {
        m_tft->fillScreen(TFT_RED);
    }
    
    // 刷新显示
    void refresh() {
        // 将显示缓冲推送到屏幕
        m_tft->fillScreen(TFT_WHITE);
    }
};

#endif // DISPLAY_CONTEXT_H
