//
// Created by Administrator on 25-4-29.
//

#include "FunctionBaudState.h"

FunctionBaudState::FunctionBaudState()
: FunctionState("FunctionBaudState")
, m_currentBaudLabel(nullptr)
, m_nextBaudLabel(nullptr)
, m_previousBaudLabel(nullptr)
, m_line(nullptr)
, m_currentBaudIndex(1)
{

}
void FunctionBaudState::onEnter()
{
    m_currentBaudLabel = lv_label_create(lv_scr_act());
    m_nextBaudLabel = lv_label_create(lv_scr_act());
    m_previousBaudLabel = lv_label_create(lv_scr_act());
    // 创建一条线对象
    m_line = lv_line_create(lv_scr_act());
    // 获取屏幕的高度和宽度
    lv_coord_t screen_width = lv_disp_get_hor_res(NULL);
    lv_coord_t screen_height = lv_disp_get_ver_res(NULL);
    // 计算水平居中时线的 y 坐标
    lv_coord_t center_y = screen_height / 2;
    // 定义线的两个端点
    static lv_point_precise_t line_points[] = {
        {0, center_y},
        {screen_width, center_y}
    };
    // 设置线的端点
    lv_line_set_points(m_line, line_points, 2);
    // 设置线的样式
    lv_obj_set_style_line_color(m_line, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_line_width(m_line, 2, 0);

    char buf[16];
    sprintf(buf, "%d", m_baudRateList[m_currentBaudIndex]);
    lv_label_set_text(m_currentBaudLabel, buf);
    lv_obj_set_pos(m_currentBaudLabel, (screen_width/2 - 20), (screen_height/2-30));
    lv_obj_set_style_text_color(m_currentBaudLabel, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(m_currentBaudLabel, &style_font_22, 0);

    uint8_t prevBaudIndex = m_currentBaudIndex - 1;
    if(prevBaudIndex < 0){
        m_currentBaudIndex = sizeof(m_baudRateList) / sizeof(m_baudRateList[0]) ;
    }
    sprintf(buf, "%d", m_baudRateList[prevBaudIndex]);
    lv_label_set_text(m_previousBaudLabel, buf);
    lv_obj_set_pos(m_previousBaudLabel, 20, (screen_height/2+10));
    lv_obj_set_style_text_color(m_previousBaudLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_previousBaudLabel, &style_font_22, 0);

    uint8_t nextBaudIndex = m_currentBaudIndex + 1;
    if(nextBaudIndex >= sizeof(m_baudRateList) / sizeof(m_baudRateList[0])){
        nextBaudIndex = 0;
    }
    sprintf(buf, "%d", m_baudRateList[nextBaudIndex]);
    lv_label_set_text(m_nextBaudLabel, buf);
    lv_obj_set_pos(m_nextBaudLabel, (screen_width - 100), (screen_height/2+10));
    lv_obj_set_style_text_color(m_nextBaudLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_nextBaudLabel, &style_font_22, 0);
}

void FunctionBaudState::onExit()
{
    if(m_currentBaudLabel != nullptr){
        lv_obj_del(m_currentBaudLabel);
        m_currentBaudLabel = nullptr;
    }
    if(m_nextBaudLabel != nullptr){
        lv_obj_del(m_nextBaudLabel);
        m_nextBaudLabel = nullptr;
    }
    if(m_previousBaudLabel != nullptr){
        lv_obj_del(m_previousBaudLabel);
        m_previousBaudLabel = nullptr;
    }
    if(m_line != nullptr){
        lv_obj_del(m_line);
        m_line = nullptr;
    }
}

bool FunctionBaudState::handleEvent(StateMachine* machine, const Event* event)
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
            // 按钮按下，进入选中的功能
            return false;
    }

    default:
        return false;
    }
}

void FunctionBaudState::updateDisplay(DisplayContext* display)
{
    if (!display) {
        return;
    }

    char buf[16];
    sprintf(buf, "%d", m_baudRateList[m_currentBaudIndex]);
    lv_label_set_text(m_currentBaudLabel, buf);

    // Correctly calculate the previous baud index
    uint8_t prevBaudIndex = (m_currentBaudIndex == 0) ? (sizeof(m_baudRateList) / sizeof(m_baudRateList[0]) - 1) : m_currentBaudIndex - 1;
    sprintf(buf, "%d", m_baudRateList[prevBaudIndex]);
    lv_label_set_text(m_previousBaudLabel, buf);

    // Correctly calculate the next baud index
    uint8_t nextBaudIndex = (m_currentBaudIndex == (sizeof(m_baudRateList) / sizeof(m_baudRateList[0]) - 1)) ? 0 : m_currentBaudIndex + 1;
    sprintf(buf, "%d", m_baudRateList[nextBaudIndex]);
    lv_label_set_text(m_nextBaudLabel, buf);

}

void FunctionBaudState::increaceBaudRate()
{
    uint8_t nextBaudIndex = (m_currentBaudIndex == (sizeof(m_baudRateList) / sizeof(m_baudRateList[0]) - 1)) ? 0 : m_currentBaudIndex + 1;
    m_currentBaudIndex = nextBaudIndex;
    m_baudRate = m_baudRateList[m_currentBaudIndex];
}

void FunctionBaudState::decreaceBaudRate()
{
    uint8_t prevBaudIndex = (m_currentBaudIndex == 0) ? (sizeof(m_baudRateList) / sizeof(m_baudRateList[0]) - 1) : m_currentBaudIndex - 1;
    m_currentBaudIndex = prevBaudIndex;
    m_baudRate = m_baudRateList[m_currentBaudIndex];
}

int FunctionBaudState::getID() const
{
    return ID;
}

const char* FunctionBaudState::getName() const
{
    return "FunctionBaudState";
}


uint FunctionBaudState::m_baudRate = BAUD_9600;

