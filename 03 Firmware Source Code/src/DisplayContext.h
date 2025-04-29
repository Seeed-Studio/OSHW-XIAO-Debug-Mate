#ifndef DISPLAY_CONTEXT_H
#define DISPLAY_CONTEXT_H

#include "FreeRTOS.h"
#include "semphr.h"

#include <lvgl.h>

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

// 显示上下文，提供绘图API
class DisplayContext {
private:
    SemaphoreHandle_t m_displayMutex;
    
public:
    DisplayContext() {
        m_displayMutex = xSemaphoreCreateMutex();
    }
    
    ~DisplayContext() {
        if (m_displayMutex) {
            vSemaphoreDelete(m_displayMutex);
        }
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
    
    // 刷新显示
    void refresh() {
        // 将显示缓冲推送到屏幕
    }
};

#endif // DISPLAY_CONTEXT_H
