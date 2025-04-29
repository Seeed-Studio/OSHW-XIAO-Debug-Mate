#include "MenuStates.h"
#include "StateManager.h"
#include "LvglStyle.h"

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
    m_currentSelection = 0;

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

    lv_obj_t* led_title = lv_led_create(m_mainMenu.screen);
    lv_obj_set_pos(led_title, 55 + 12 + 50 + 110 + 3, 28);
    lv_led_on(led_title);
    lv_led_set_color(led_title, lv_color_hex(0xACE62F));
    lv_obj_add_style(led_title, &style_led, 0);

    // Left Block
    m_mainMenu.uart_bg = lv_obj_create(m_mainMenu.screen);
    lv_obj_set_size(m_mainMenu.uart_bg, 108, 154);
    lv_obj_set_pos(m_mainMenu.uart_bg, 12 + 12, 62);
    lv_obj_add_style(m_mainMenu.uart_bg, &style_uart_bg, 0);

    // Baud
    label = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(label, "Baud");
    lv_obj_set_pos(label, 0, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xA6ACAF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_12, 0);

    // 115200
    m_mainMenu.baud_value = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(m_mainMenu.baud_value, "9600");
    lv_obj_set_pos(m_mainMenu.baud_value, 0, 18);
    lv_obj_set_style_text_color(m_mainMenu.baud_value, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.baud_value, &style_font_20, 0);

    // RX
    label = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(label, "RX");
    lv_obj_set_pos(label, 0, 58);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);

    lv_obj_t* led_RX = lv_led_create(m_mainMenu.uart_bg);
    lv_obj_set_pos(led_RX, 40, 64);
    lv_led_on(led_RX);
    lv_led_set_color(led_RX, lv_color_hex(0xDDE62F));
    lv_obj_add_style(led_RX, &style_led, 0);

    // TX
    label = lv_label_create(m_mainMenu.uart_bg);
    lv_label_set_text(label, "TX");
    lv_obj_set_pos(label, 0, 94);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_18, 0);

    lv_obj_t* led_TX = lv_led_create(m_mainMenu.uart_bg);
    lv_obj_set_pos(led_TX, 40, 100);
    lv_led_on(led_TX);
    lv_led_set_color(led_TX, lv_color_hex(0x2FE6AC));
    lv_obj_add_style(led_TX, &style_led, 0);

    // Right Block
    lv_obj_t* power_bg = lv_obj_create(m_mainMenu.screen);
    lv_obj_set_size(power_bg, 152, 154);
    lv_obj_set_pos(power_bg, 12 + 132, 62);
    lv_obj_add_style(power_bg, &style_power_bg, 0);

    // 电压
    label = lv_label_create(power_bg);
    lv_label_set_text(label, "U");
    lv_obj_set_pos(label, 12, 20);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_22, 0);

    label = lv_label_create(power_bg);
    lv_label_set_text(label, "V");
    lv_obj_set_pos(label, 123, 28);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // 电流
    label = lv_label_create(power_bg);
    lv_label_set_text(label, "I");
    lv_obj_set_pos(label, 12, 64);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_22, 0);

    label = lv_label_create(power_bg);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 123, 72);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // 功耗
    label = lv_label_create(power_bg);
    lv_label_set_text(label, "P");
    lv_obj_set_pos(label, 12, 107);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_22, 0);

    label = lv_label_create(power_bg);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 123, 115);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // value
    m_mainMenu.vol = lv_label_create(power_bg);
    lv_label_set_text(m_mainMenu.vol, "5.0345");
    lv_obj_set_pos(m_mainMenu.vol, 41, 20);
    lv_obj_set_style_text_color(m_mainMenu.vol, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.vol, &style_font_22, 0);

    m_mainMenu.cur = lv_label_create(power_bg);
    lv_label_set_text(m_mainMenu.cur, "0.0182");
    lv_obj_set_pos(m_mainMenu.cur, 41, 64);
    lv_obj_set_style_text_color(m_mainMenu.cur, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_mainMenu.cur, &style_font_22, 0);

    m_mainMenu.power = lv_label_create(power_bg);
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
        case EVENT_WHEEL_CLOCKWISE: {
            // 滚轮顺时针，选择下一项
            if (m_itemCount > 0) {
                m_currentSelection = (m_currentSelection + 1) % m_itemCount;
                return true;
            }
            return false;
        }
        
        case EVENT_WHEEL_COUNTERCLOCKWISE: {
            // 滚轮逆时针，选择上一项
            if (m_itemCount > 0) {
                m_currentSelection = (m_currentSelection + m_itemCount - 1) % m_itemCount;
                return true;
            }
            return false;
        }
        
        case EVENT_BUTTON_PRESS: {
            // 按钮按下，进入选中的功能
            const ButtonEvent* buttonEvent = static_cast<const ButtonEvent*>(event);
            if (buttonEvent->getButtonId() == 0) { // 假设0是确认按钮
                if (m_itemCount > 0) {
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
}

void MainMenuState::updateDisplay(DisplayContext* display) {
    if (!display) {
        return;
    }

    char value[10];
    int baud_value = 9600;
    float vol = 0;
    float cur = 0;
    float power = 0;

    lv_label_set_text_fmt(m_mainMenu.baud_value, "%d", baud_value);

    snprintf(value, sizeof(value), "%.4f", vol);
    lv_label_set_text(m_mainMenu.vol, value);

    snprintf(value, sizeof(value), "%.4f", cur);
    lv_label_set_text(m_mainMenu.cur, value);

    snprintf(value, sizeof(value), "%.4f", power);
    lv_label_set_text(m_mainMenu.power, value);
}

// FunctionState基类实现
void FunctionState::onEnter() {
    // 功能状态共用进入逻辑
}

void FunctionState::onExit() {
    // 功能状态共用退出逻辑
}

bool FunctionState::handleEvent(StateMachine* machine, const Event* event) {
    if (!machine || !event) {
        return false;
    }
    
    switch (event->getType()) {
        case EVENT_BUTTON_PRESS: {
            // 按钮按下，检查是否是返回按钮
            const ButtonEvent* buttonEvent = static_cast<const ButtonEvent*>(event);
            if (buttonEvent->getButtonId() == 1) { // 假设1是返回按钮
                // 返回主菜单
                State* mainMenu = StateManager::getInstance()->getState(MainMenuState::ID);
                if (mainMenu) {
                    machine->changeState(mainMenu);
                    return true;
                }
            }
            return false;
        }
        
        default:
            return false;
    }
}

// Function1State实现
void Function1State::updateDisplay(DisplayContext* display) {
    if (!display) {
        return;
    }
    
    display->lock();
    
    // 清屏
    display->clear();
    
    // 绘制标题
    display->drawText(10, 10, m_title, true);
    
    // 绘制功能内容
    display->drawText(10, 40, "This is Function 1");
    display->drawText(10, 60, "Press back button to return");
    
    // 刷新显示
    display->refresh();
    
    display->unlock();
}

// ErrorState实现
ErrorState::ErrorState() 
    : m_errorCode(0), 
      m_errorMessage("Unknown error") 
{
}

void ErrorState::setError(int code, const char* message) {
    m_errorCode = code;
    m_errorMessage = message;
}

void ErrorState::onEnter() {
    // 记录错误信息到日志
}

bool ErrorState::handleEvent(StateMachine* machine, const Event* event) {
    if (!machine || !event) {
        return false;
    }
    
    // 任何按钮按下都返回主菜单
    if (event->getType() == EVENT_BUTTON_PRESS) {
        State* mainMenu = StateManager::getInstance()->getState(MainMenuState::ID);
        if (mainMenu) {
            machine->changeState(mainMenu);
            return true;
        }
    }
    
    return false;
}

void ErrorState::updateDisplay(DisplayContext* display) {
    if (!display) {
        return;
    }
    
    display->lock();
    
    // 清屏
    display->clear();
    
    // 绘制错误信息
    display->drawText(10, 10, "ERROR", true);
    
    char errorText[32];
    sprintf(errorText, "Code: %d", m_errorCode);
    display->drawText(10, 40, errorText);
    
    display->drawText(10, 60, m_errorMessage);
    display->drawText(10, 100, "Press any button to return");
    
    // 刷新显示
    display->refresh();
    
    display->unlock();
}
