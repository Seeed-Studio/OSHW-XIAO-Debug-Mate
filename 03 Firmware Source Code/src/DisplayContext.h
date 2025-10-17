#ifndef DISPLAY_CONTEXT_H
#define DISPLAY_CONTEXT_H

#include "FreeRTOS.h"
#include "semphr.h"
#include "Global.h"

#include <Adafruit_INA228.h>
#include <lvgl.h>

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

// 显示上下文，提供绘图API
class DisplayContext {
private:
    SemaphoreHandle_t m_displayMutex;
    Adafruit_INA228* m_ina228;

public:
    DisplayContext() {
        m_displayMutex = xSemaphoreCreateMutex();
    }

    ~DisplayContext() {
        if (m_displayMutex) {
            vSemaphoreDelete(m_displayMutex);
        }
    }

    void setINA228(Adafruit_INA228* ina228) {
        m_ina228 = ina228;
        m_ina228->setAveragingCount(INA228_COUNT_16);
        m_ina228->setVoltageConversionTime(INA228_TIME_4120_us);
        m_ina228->setCurrentConversionTime(INA228_TIME_4120_us);
    }

    void updateShuntOfINA() {
        int mos1 = 0, mos2 = 0;

        mos1 = digitalRead(MOS1_PIN);
        mos2 = digitalRead(MOS2_PIN);
        if (mos1 == 0 && mos2 == 0) {
            m_ina228->setShunt(9.936290, 0.0062);
        } else if(mos1 == 1 && mos2 == 0) {
            m_ina228->setShunt(1.023875, 0.1394);
        } else if(mos1 == 1 && mos2 == 1) {
            m_ina228->setShunt(0.105482, 1.0);
        }
    }

    Adafruit_INA228* getINA228() {
        updateShuntOfINA();
        return m_ina228;
    }

    void updateBaudLED(int baudIndex, bool background = true) {
        byte dataA = 0B00000000, dataB = 0B10000000;

        if (!background) {
            dataB = 0B00000000;
        }

        if (baudIndex <= 6) {
            dataA |= 2 << baudIndex;
        } else {
            dataB |= 1 << (baudIndex - 7);
        }

        digitalWrite(LED_LATCH, LOW);

        shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, dataB);
        shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, dataA);

        digitalWrite(LED_LATCH, HIGH);
    }

    // 获取显示锁
    bool lock(TickType_t timeout = portMAX_DELAY) {
        return (xSemaphoreTake(m_displayMutex, timeout) == pdTRUE);
    }
    
    // 释放显示锁
    void unlock() {
        xSemaphoreGive(m_displayMutex);
    }
};

#endif // DISPLAY_CONTEXT_H
