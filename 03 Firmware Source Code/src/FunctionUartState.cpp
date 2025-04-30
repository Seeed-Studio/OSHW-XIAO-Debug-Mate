//
// Created by Administrator on 25-4-29.
//

#include "FunctionUartState.h"

FunctionUartState::FunctionUartState()
: FunctionState("FunctionUartState")
, m_uartType(UartType::UART_TYPE_XIAO)
, m_uartUI()
{

}

void FunctionUartState::onEnter()
{
    if (m_uartUI.UartScreen != nullptr) {
        if ( lv_scr_act() != m_uartUI.UartScreen) {
            lv_scr_load(m_uartUI.UartScreen);
        }
        return;
    }
    m_uartUI.UartScreen = lv_obj_create(NULL);
    lv_obj_add_style(m_uartUI.UartScreen, &style_screen, 0);

    // 创建UI标签
    m_uartUI.UartTypeBg = lv_obj_create(m_uartUI.UartScreen);
    m_uartUI.UartBaudBg = lv_obj_create(m_uartUI.UartScreen);
    m_uartUI.UartRxBg = lv_obj_create(m_uartUI.UartScreen);
    m_uartUI.UartTxBg = lv_obj_create(m_uartUI.UartScreen);
    m_uartUI.UartTypeLabel = lv_label_create(m_uartUI.UartScreen);
    m_uartUI.UartBaudLabel = lv_label_create(m_uartUI.UartScreen);
    m_uartUI.UartRxLabel = lv_label_create(m_uartUI.UartRxBg);
    m_uartUI.UartTxLabel = lv_label_create(m_uartUI.UartTxBg);

    // 画背景块
    lv_obj_add_style(m_uartUI.UartScreen, &style_screen, 0);

    lv_obj_set_size(m_uartUI.UartTypeBg , 100, 40);
    lv_obj_set_pos(m_uartUI.UartTypeBg , 20, 20);
    lv_obj_add_style(m_uartUI.UartTypeBg , &style_uart_bg, 0);

    lv_obj_set_size(m_uartUI.UartBaudBg , 100, 40);
    lv_obj_set_pos(m_uartUI.UartBaudBg , 20+160, 20);
    lv_obj_add_style(m_uartUI.UartBaudBg , &style_power_bg, 0);

    lv_obj_set_size(m_uartUI.UartRxBg , 230, 70);
    lv_obj_set_pos(m_uartUI.UartRxBg , 70, 70);
    lv_obj_add_style(m_uartUI.UartRxBg , &style_power_bg, 0);

    lv_obj_set_size(m_uartUI.UartTxBg  , 230, 70);
    lv_obj_set_pos(m_uartUI.UartTxBg  , 70, 70+80);
    lv_obj_add_style(m_uartUI.UartTxBg  , &style_power_bg, 0);

    // 画元素
    // UART
    lv_obj_t* label = lv_label_create(m_uartUI.UartScreen);
    lv_obj_set_pos(label, 25, 30);
    lv_label_set_text(label, "UART:");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_12, 0);
    lv_label_set_text_fmt(m_uartUI.UartTypeLabel, "%s", (m_uartType == UartType::UART_TYPE_XIAO)? "XIAO" : "Grove");
    lv_obj_set_pos(m_uartUI.UartTypeLabel,65,30);
    lv_obj_set_style_text_color(m_uartUI.UartTypeLabel, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_uartUI.UartTypeLabel, &style_font_18, 0);

    // 波特率
    lv_label_set_text_fmt(m_uartUI.UartBaudLabel, "%d", FunctionBaudState::m_baudRate);
    lv_obj_set_pos(m_uartUI.UartBaudLabel, 20+160+20, 30);
    lv_obj_set_style_text_color(m_uartUI.UartBaudLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_uartUI.UartBaudLabel, &style_font_22, 0);

    // RX
    label = lv_label_create(m_uartUI.UartScreen);
    lv_label_set_text(label, "RX");
    lv_obj_set_pos(label, 20, 75);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);
    // RX LED
    lv_obj_t* led_RX = lv_led_create(m_uartUI.UartScreen);
    lv_obj_set_pos(led_RX, 20+30, 75+5);
    lv_led_on(led_RX);
    lv_led_set_color(led_RX, lv_color_hex(0xDDE62F));
    lv_obj_add_style(led_RX, &style_led, 0);

    // TX
    label = lv_label_create(m_uartUI.UartScreen);
    lv_label_set_text(label, "TX");
    lv_obj_set_pos(label, 20, 75+80);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);
    // TX LED
    lv_obj_t* led_TX = lv_led_create(m_uartUI.UartScreen);
    lv_obj_set_pos(led_TX, 20+30, 75+80+5);
    lv_led_on(led_TX);
    lv_led_set_color(led_TX, lv_color_hex(0x2FE6AC));
    lv_obj_add_style(led_TX, &style_led, 0);

    lv_scr_load(m_uartUI.UartScreen);
}

void FunctionUartState::onExit()
{
    // 销毁父对象
    if (m_uartUI.UartScreen != nullptr) {
        lv_obj_del(m_uartUI.UartScreen);
        m_uartUI.UartScreen = nullptr;
    }
}

bool FunctionUartState::handleEvent(StateMachine* machine, const Event* event)
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
            //滚轮逆时针，选择上一项
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

// Function1State实现
void FunctionUartState::updateDisplay(DisplayContext* display) {
    if (!display) {
        return;
    }

    lv_label_set_text_fmt(m_uartUI.UartTypeLabel, "%s", (m_uartType == UartType::UART_TYPE_XIAO)? "XIAO" : "Grove");
    lv_label_set_text_fmt(m_uartUI.UartBaudLabel, "%d", FunctionBaudState::m_baudRate);

    lv_label_set_text(m_uartUI.UartRxLabel, m_rxBuff);
    lv_label_set_text(m_uartUI.UartTxLabel, m_txBuff);

    // static bool flag = false;
    // if(flag)
    // {
    //     lv_obj_add_style(m_uartUI.UartTypeBg , &style_uart_bg, 0);
    //     lv_obj_add_style(m_uartUI.UartBaudBg , &style_power_bg, 0);
    //
    // }else
    // {
    //     lv_obj_add_style(m_uartUI.UartTypeBg , &style_power_bg, 0);
    //     lv_obj_add_style(m_uartUI.UartBaudBg , &style_uart_bg, 0);
    // }
    // changeUartType();
    // flag = !flag;
}

int FunctionUartState::getID() const
{
    return ID;
}

const char* FunctionUartState::getName() const
{
    return "FunctionUartState";
}

void FunctionUartState::changeUartType()
{
    if(m_uartType == UartType::UART_TYPE_XIAO){
        m_uartType = UartType::UART_TYPE_Grove;
    }else{
        m_uartType = UartType::UART_TYPE_XIAO;
    }
}


