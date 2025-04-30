//
// Created by Administrator on 25-4-29.
//

#include "FunctionPowerState.h"

FunctionPowerState::FunctionPowerState()
: FunctionState("FunctionPowerState")
, m_voltageLabel_V(nullptr)
, m_currentLabel_A(nullptr)
, m_currentLabel_mA(nullptr)
, m_currentLabel_uA(nullptr)
, m_powerLabel_W(nullptr)
, m_powerLabel_mW(nullptr)
, m_minLabel(nullptr)
, m_maxLabel(nullptr)
, m_totalLabel(nullptr)
, m_timeLabel(nullptr)
, m_voltage(0.0)
, m_current(0.0)
, m_power(0.0)
{
}

void FunctionPowerState::onEnter()
{
    // m_titleLabel = lv_label_create(lv_scr_act());
    m_voltageLabel_V = lv_label_create(lv_scr_act());
    m_currentLabel_A = lv_label_create(lv_scr_act());
    m_currentLabel_mA = lv_label_create(lv_scr_act());
    m_currentLabel_uA = lv_label_create(lv_scr_act());
    m_powerLabel_W = lv_label_create(lv_scr_act());
    m_powerLabel_mW = lv_label_create(lv_scr_act());
    m_minLabel = lv_label_create(lv_scr_act());
    m_maxLabel = lv_label_create(lv_scr_act());
    m_totalLabel = lv_label_create(lv_scr_act());
    m_timeLabel = lv_label_create(lv_scr_act());
    powerInterface_1();
}

void FunctionPowerState::onExit()
{
    // if(m_titleLabel != nullptr){
    //     lv_obj_del(m_titleLabel);
    //     m_titleLabel = nullptr;
    // }
    if (m_voltageLabel_V != nullptr) {
        lv_obj_del(m_voltageLabel_V);
        m_voltageLabel_V = nullptr;
    }
    if (m_currentLabel_A != nullptr) {
        lv_obj_del(m_currentLabel_A);
        m_currentLabel_A = nullptr;
    }
    if (m_powerLabel_W != nullptr){
        lv_obj_del(m_powerLabel_W);
        m_powerLabel_W = nullptr;
    }
    if (m_minLabel != nullptr) {
        lv_obj_del(m_minLabel);
        m_minLabel = nullptr;
    }
    if (m_maxLabel != nullptr) {
        lv_obj_del(m_maxLabel);
        m_maxLabel = nullptr;
    }
    if (m_totalLabel != nullptr) {
        lv_obj_del(m_totalLabel);
        m_totalLabel = nullptr;
    }
    if (m_timeLabel != nullptr) {
        lv_obj_del(m_timeLabel);
        m_timeLabel = nullptr;
    }
}

bool FunctionPowerState::handleEvent(StateMachine* machine, const Event* event)
{
    if (!machine || !event) {
        return false;
    }

    switch (event->getType()) {
    case EVENT_WHEEL_CLOCKWISE: {
            // 滚轮顺时针，选择下一项
            return false;
    }

    case EVENT_WHEEL_COUNTERCLOCKWISE: {
            // 滚轮逆时针，选择上一项
            return false;
    }

    case EVENT_BUTTON_PRESS: {

            return false;
    }

    default:
        return false;
    }
}

void FunctionPowerState::updateDisplay(DisplayContext* display)
{
    if (!display) {
        return;
    }

    char buff[16];
    sprintf(buff, "U %.4f v", m_voltage);
    lv_label_set_text(m_voltageLabel_V, buff);
    sprintf(buff, "I  %.4f A", m_current);
    lv_label_set_text(m_currentLabel_A, buff);
    sprintf(buff, "P %.4f v", m_power);
    lv_label_set_text(m_powerLabel_W, buff);
}

int FunctionPowerState::getID() const
{
    return ID;
}

const char* FunctionPowerState::getName() const
{
    return "FunctionPowerState";
}

void FunctionPowerState::powerInterface_1()
{
    // 电压
    char buf[16];
    sprintf(buf, "U %.4f v", m_voltage);
    lv_label_set_text(m_voltageLabel_V, buf);
    lv_obj_set_pos(m_voltageLabel_V, 42, 30);
    lv_obj_set_style_text_color(m_voltageLabel_V, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(m_voltageLabel_V, &style_font_36, 0);

    // 电流
    sprintf(buf, "I %.4f A", m_current);
    lv_label_set_text(m_currentLabel_A, buf);
    lv_obj_set_pos(m_currentLabel_A, 42, 94);
    lv_obj_set_style_text_color(m_currentLabel_A, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_currentLabel_A, &style_font_36, 0);

    // 功耗
    sprintf(buf, "P %.4f W", m_power);
    lv_label_set_text(m_powerLabel_W, buf);
    lv_obj_set_pos(m_powerLabel_W, 42, 157);
    lv_obj_set_style_text_color(m_powerLabel_W, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(m_powerLabel_W, &style_font_36, 0);
}

void FunctionPowerState::powerInterface_2()
{

    char buf[16];
    // 电压
    sprintf(buf, "U %.4f v", m_voltage);
    lv_label_set_text(m_voltageLabel_V, buf);
    lv_obj_set_pos(m_voltageLabel_V, 42, 40);
    lv_obj_set_style_text_color(m_voltageLabel_V, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(m_voltageLabel_V, &style_font_22, 0);

    // 电流
    sprintf(buf, "I %.4f A", m_current);
    lv_label_set_text(m_currentLabel_A, buf);
    lv_obj_set_pos(m_currentLabel_A, 42, 70);
    lv_obj_set_style_text_color(m_currentLabel_A, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_currentLabel_A, &style_font_22, 0);

    sprintf(buf, " %.4f mA", m_current*1000);
    lv_label_set_text(m_currentLabel_mA, buf);
    lv_obj_set_pos(m_currentLabel_mA, 9, 30);
    lv_obj_set_style_text_color(m_currentLabel_mA, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_currentLabel_mA, &style_font_22, 0);

    sprintf(buf, " %.1f uA", m_current*1000000);
    lv_label_set_text(m_currentLabel_uA, buf);
    lv_obj_set_pos(m_currentLabel_uA, 9, 60);
    lv_obj_set_style_text_color(m_currentLabel_uA, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_currentLabel_uA, &style_font_22, 0);


    // 功耗
    sprintf(buf, "P %.4f W", m_power);
    lv_label_set_text(m_powerLabel_W, buf);
    lv_obj_set_pos(m_powerLabel_W, 42, 160);
    lv_obj_set_style_text_color(m_powerLabel_W, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(m_powerLabel_W, &style_font_22, 0);

    sprintf(buf, " %.4f mW", m_power*1000);
    lv_label_set_text(m_powerLabel_mW, buf);
    lv_obj_set_pos(m_powerLabel_mW, 20, 30);
    lv_obj_set_style_text_color(m_powerLabel_mW, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(m_powerLabel_mW, &style_font_22, 0);
}

void FunctionPowerState::powerInterface_3()
{
    char buf[16];

    lv_label_set_text(m_minLabel, "Min");
    lv_obj_set_pos(m_minLabel, 30, 30);
    lv_obj_set_style_text_color(m_minLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_minLabel, &style_font_18, 0);

    lv_label_set_text(m_maxLabel, "Max");
    lv_obj_set_pos(m_maxLabel, 180, 30);
    lv_obj_set_style_text_color(m_maxLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_maxLabel, &style_font_18, 0);

    lv_label_set_text(m_totalLabel, "Total");
    lv_obj_set_pos(m_totalLabel, 30, 130);
    lv_obj_set_style_text_color(m_totalLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_totalLabel, &style_font_18, 0);


    unsigned long currentTime = millis() - startTime;
    unsigned long seconds = currentTime / 1000;
    unsigned long minutes = seconds / 60;
    seconds = seconds % 60;
    unsigned long hours = minutes / 60;
    minutes = minutes % 60;
    char time[16];
    // 格式化时间为 00:00:00 格式，并使用换行符实现上下展示
    sprintf(time, "Time\n%02lu:%02lu:%02lu", hours, minutes, seconds);
    lv_label_set_text(m_timeLabel, time);
    lv_obj_set_pos(m_timeLabel, 180, 130);
    lv_obj_set_style_text_color(m_timeLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_timeLabel, &style_font_18, 0);
}
