#include "Global.h"
#include "Tool.h"
#include "MenuStates.h"
#include "StateManager.h"
#include "LvglStyle.h"
#include "FunctionBaudState.h"
#include "DapLink.h"

// MainMenuState实现
MainMenuState::MainMenuState() 
    : m_itemCount(0), 
      m_currentSelection(0) 
{
    // 初始化菜单项数组
    for (int i = 0; i < MAX_ITEMS; ++i) {
        m_items[i].label = nullptr;
        m_items[i].stateId = 0;
    }

    m_mainMenu = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    };
}

bool MainMenuState::addMenuItem(const char* label, int stateId) {
    if (m_itemCount >= MAX_ITEMS) {
        return false;
    }
    
    m_items[m_itemCount].label = label;
    m_items[m_itemCount].stateId = stateId;
    m_itemCount++;
    
    return true;
}

void MainMenuState::onEnter() {
    // 重置选择位置
    m_currentSelection = -1;

    if (m_mainMenu.screen != nullptr) {
        if ( lv_scr_act() != m_mainMenu.screen) {
            lv_scr_load(m_mainMenu.screen);
        }
        return;
    }

    m_mainMenu.screen = lv_obj_create(NULL);

    lv_obj_add_style(m_mainMenu.screen, &style_screen, 0);

    // Title
    lv_obj_t* label = lv_label_create(m_mainMenu.screen);
    lv_label_set_text( label, "SWD" );
    lv_obj_set_pos( label, 55 + 12, 23 ); // 62 + *
    lv_obj_set_style_text_color(label, lv_color_hex(0xA6ACAF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);

    label = lv_label_create(m_mainMenu.screen);
    lv_label_set_text( label, "DEBUG" );
    lv_obj_set_pos( label, 55 + 12 + 50, 18 );
    lv_obj_set_style_text_color(label, lv_color_hex(0xACE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_28, 0);

    label = lv_label_create(m_mainMenu.screen);
    lv_label_set_text( label, "v1.0" );
    lv_obj_align_to(label, m_mainMenu.screen, LV_ALIGN_TOP_RIGHT, -40, 38);
    lv_obj_set_style_text_color(label, lv_color_hex(0x808080), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    m_mainMenu.ledTitle = lv_led_create(m_mainMenu.screen);
    lv_obj_set_pos(m_mainMenu.ledTitle, 55 + 12 + 50 + 110 + 3, 28);
    lv_led_on(m_mainMenu.ledTitle);
    if (daplinkStatus) {
        lv_led_set_color(m_mainMenu.ledTitle, lv_color_hex(0xACE62F));
    } else {
        lv_led_set_color(m_mainMenu.ledTitle, lv_color_hex(0xFF0000));
    }
    lv_obj_add_style(m_mainMenu.ledTitle, &style_led, 0);

    // Left Block
    m_mainMenu.uart_bg = lv_obj_create(m_mainMenu.screen);
    lv_obj_set_size(m_mainMenu.uart_bg, 108, 154);
    lv_obj_set_pos(m_mainMenu.uart_bg, 12 + 12, 62);
    lv_obj_add_style(m_mainMenu.uart_bg, &style_nofocus_bg, 0);

    // Baud
    label = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(label, "Baud");
    lv_obj_set_pos(label, 12, 13);
    lv_obj_set_style_text_color(label, lv_color_hex(0xA6ACAF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_12, 0);

    // Baud Value
    m_mainMenu.baudRate = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(m_mainMenu.baudRate, "9600");
    lv_obj_set_pos(m_mainMenu.baudRate, 13, 33);
    lv_obj_set_style_text_color(m_mainMenu.baudRate, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.baudRate, &style_font_20, 0);

    // RX
    label = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(label, "RX");
    lv_obj_set_pos(label, 13, 70);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);

    m_mainMenu.ledRx = lv_led_create(m_mainMenu.uart_bg);
    lv_obj_set_pos(m_mainMenu.ledRx, 45, 77);
    lv_led_off(m_mainMenu.ledRx);
    lv_led_set_color(m_mainMenu.ledRx, lv_color_hex(0xDDE62F));
    lv_obj_add_style(m_mainMenu.ledRx, &style_led, 0);

    // TX
    label = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(label, "TX");
    lv_obj_set_pos(label, 13, 109);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);

    m_mainMenu.ledTx = lv_led_create(m_mainMenu.uart_bg);
    lv_obj_set_pos(m_mainMenu.ledTx, 45, 115);
    lv_led_off(m_mainMenu.ledTx);
    lv_led_set_color(m_mainMenu.ledTx, lv_color_hex(0x2FE6AC));
    lv_obj_add_style(m_mainMenu.ledTx, &style_led, 0);

    // Right Block
    m_mainMenu.power_bg = lv_obj_create(m_mainMenu.screen);
    lv_obj_set_size(m_mainMenu.power_bg, 152, 154);
    lv_obj_set_pos(m_mainMenu.power_bg, 12 + 132, 62);
    lv_obj_add_style(m_mainMenu.power_bg, &style_nofocus_bg, 0);

    // 电压
    label = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(label, "U");
    lv_obj_set_pos(label, 12, 20);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_22, 0);

    label = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(label, "V");
    lv_obj_set_pos(label, 123, 28);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // 电流
    label = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(label, "I");
    lv_obj_set_pos(label, 12, 64);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_22, 0);

    label = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 123, 72);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // 功耗
    label = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(label, "P");
    lv_obj_set_pos(label, 12, 107);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_22, 0);

    label = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 123, 115);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // value
    m_mainMenu.vol = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(m_mainMenu.vol, "5.0345");
    lv_obj_set_pos(m_mainMenu.vol, 41, 20);
    lv_obj_set_style_text_color(m_mainMenu.vol, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.vol, &style_font_22, 0);

    m_mainMenu.cur = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(m_mainMenu.cur, "0.0182");
    lv_obj_set_pos(m_mainMenu.cur, 41, 64);
    lv_obj_set_style_text_color(m_mainMenu.cur, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.cur, &style_font_22, 0);

    m_mainMenu.power = lv_label_create(m_mainMenu.power_bg);
    lv_label_set_text(m_mainMenu.power, "0.0934");
    lv_obj_set_pos(m_mainMenu.power, 41, 64);
    lv_obj_set_pos(m_mainMenu.power, 41, 107);
    lv_obj_set_style_text_color(m_mainMenu.power, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.power, &style_font_22, 0);

    lv_scr_load(m_mainMenu.screen);
}

void MainMenuState::onExit() {
    // 清理工作
}

bool MainMenuState::handleEvent(StateMachine* machine, const Event* event) {
    if (!machine || !event) {
        return false;
    }
    
    switch (event->getType()) {
        case EVENT_WHEEL_CLOCKWISE:
        case EVENT_WHEEL_COUNTERCLOCKWISE: {
            if (m_currentSelection < 0) {
                m_currentSelection = 0;
            } else {
                m_currentSelection = !m_currentSelection;
            }

            return true;
        }
        
        case EVENT_BUTTON_PRESS: {
            if (m_currentSelection < 0) {
                m_currentSelection = 0;
                break;
            }

            const ButtonEvent* buttonEvent = static_cast<const ButtonEvent*>(event);
            if (buttonEvent->getButtonId() == BOOT_BTN) {
                if (m_currentSelection != -1) {
                    int stateId = m_items[m_currentSelection].stateId;
                    State* nextState = StateManager::getInstance()->getState(stateId);
                    if (nextState) {
                        machine->changeState(nextState);
                        return true;
                    }
                }
            }
            return false;
        }

        default:
            return false;
    }

    return true;
}

void MainMenuState::updateDisplay(DisplayContext* display) {
    if (!display) {
        return;
    }

    Adafruit_INA228* ina228 = nullptr;
    char value[7] = "";
    double vol = 0, cur = 0, power = 0;

    if (m_currentSelection == -1) {
        lv_obj_add_style(m_mainMenu.uart_bg, &style_nofocus_bg, 0);
        lv_obj_add_style(m_mainMenu.power_bg, &style_nofocus_bg, 0);
    } else if (m_currentSelection == 0) {
        lv_obj_add_style(m_mainMenu.uart_bg, &style_focus_bg, 0);
        lv_obj_add_style(m_mainMenu.power_bg, &style_nofocus_bg, 0);
    } else if (m_currentSelection == 1) {
        lv_obj_add_style(m_mainMenu.uart_bg, &style_nofocus_bg, 0);
        lv_obj_add_style(m_mainMenu.power_bg, &style_focus_bg, 0);
    }

    // Title LED
    if (getUSBDeviceState() == 1) {
        lv_led_set_color(m_mainMenu.ledTitle, lv_color_hex(0xACE62F));
    } else {
        lv_led_set_color(m_mainMenu.ledTitle, lv_color_hex(0xFF0000));
    }

    // RX
    if (COMSerial.available()) {
        lv_led_on(m_mainMenu.ledRx);
    } else {
        lv_led_off(m_mainMenu.ledRx);
    }

    // TX
    if (ShowSerial.available()) {
        lv_led_on(m_mainMenu.ledTx);
    } else {
        lv_led_off(m_mainMenu.ledTx);
    }

    ina228 = display->getINA228();
    // V
    vol = (ina228->readBusVoltage() / 1000 - ina228->readShuntVoltage()) / 1000;
    // A
    cur = _max(0.0, ina228->readCurrent() / 1000 + getCompensation(ina228));
    cur = (cur <= 0.000001) ? 0 : cur;
    // W
    power = vol * cur;

    lv_label_set_text_fmt(m_mainMenu.baudRate, "%d", FunctionBaudState::m_baudRate);

    snprintf(value, sizeof(value), "%.4f", vol);
    lv_label_set_text(m_mainMenu.vol, value);

    snprintf(value, sizeof(value), "%.4f", cur);
    lv_label_set_text(m_mainMenu.cur, value);

    // 超过 1A 标签改成红色
    lv_obj_set_style_text_color(
        m_mainMenu.cur, 
        lv_color_hex(cur > 1.0f ? 0xFF0000 : 0xFFFFFF), 
        LV_PART_MAIN
    );

    snprintf(value, sizeof(value), "%.4f", power);
    lv_label_set_text(m_mainMenu.power, value);
}
