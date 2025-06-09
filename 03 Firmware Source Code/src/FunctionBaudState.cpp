#include "FunctionBaudState.h"

FunctionBaudState::FunctionBaudState()
    : FunctionState("FunctionBaudState"),
      m_currentBaudIndex(1),
      m_currentLedIndex(1),
      m_exit(false)
{
    m_baudStateUI.screen = nullptr;
    m_baudStateUI.roller = nullptr;

    for (int i = 0; i < NUM_BAUDRATES; i++) {
        m_baudStateUI.labels[i] = nullptr;
    }
}

void FunctionBaudState::onEnter()
{
    m_exit = false;

    if (m_baudStateUI.screen != nullptr) {
        if (lv_scr_act() != m_baudStateUI.screen) {
            lv_scr_load(m_baudStateUI.screen);
        }
        return;
    }

    m_baudStateUI.screen = lv_obj_create(NULL);
    lv_obj_add_style(m_baudStateUI.screen, &style_screen, 0);

    m_baudStateUI.roller = lv_obj_create(m_baudStateUI.screen);
    lv_obj_set_size(m_baudStateUI.roller, 272, 88);
    lv_obj_center(m_baudStateUI.roller);
    lv_obj_set_scroll_dir(m_baudStateUI.roller, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(m_baudStateUI.roller, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(m_baudStateUI.roller, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(m_baudStateUI.roller, lv_color_hex(0x000000), 0);
    lv_obj_set_style_pad_column(m_baudStateUI.roller, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(m_baudStateUI.roller, 0, LV_PART_MAIN);

    lv_obj_t* center_line = lv_obj_create(m_baudStateUI.screen);
    lv_obj_set_size(center_line, 272, 4);
    lv_obj_set_style_bg_color(center_line, lv_color_hex(0xACE62F), 0);
    lv_obj_set_style_bg_opa(center_line, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(center_line, 0, 0);
    lv_obj_align_to(center_line, m_baudStateUI.roller, LV_ALIGN_CENTER, 0, 0);

    for (int i = 0; i < NUM_BAUDRATES; i++) {
        lv_obj_t* item = lv_obj_create(m_baudStateUI.roller);
        lv_obj_set_height(item, 40);
        lv_obj_clear_flag(item, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_bg_opa(item, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(item, 0, 0);
        lv_obj_set_style_pad_all(item, 0, 0);

        static lv_point_precise_t p[] = {{0, 0}, {0, 10}};
        lv_obj_t* line = lv_line_create(m_baudStateUI.roller);
        lv_obj_add_style(line, &style_focus_uart_line, LV_PART_MAIN);
        lv_line_set_points(line, p, 2);

        m_baudStateUI.labels[i] = lv_label_create(item);
        lv_label_set_text(m_baudStateUI.labels[i], String(m_baudRateList[i]).c_str());
        lv_obj_set_style_text_font(m_baudStateUI.labels[i], &lv_font_montserrat_26, 0);
        lv_obj_set_style_text_color(m_baudStateUI.labels[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_center(m_baudStateUI.labels[i]);

        lv_obj_align_to(item, m_baudStateUI.roller, LV_ALIGN_CENTER, i * 100, (i % 2) ? -30 : 30);
        lv_obj_align_to(line, m_baudStateUI.roller, LV_ALIGN_CENTER, i * 100, (i % 2) ? -5 : 5);
    }

    lv_obj_scroll_to_x(m_baudStateUI.roller, 100 * m_currentBaudIndex, LV_ANIM_OFF);
    lv_obj_set_style_text_color(m_baudStateUI.labels[m_currentBaudIndex], lv_color_hex(0xACE62F), LV_PART_MAIN);

    lv_scr_load(m_baudStateUI.screen);
}

void FunctionBaudState::onExit()
{
}

bool FunctionBaudState::handleEvent(StateMachine* machine, const Event* event)
{
    if (!machine || !event) {
        return false;
    }

    switch (event->getType()) {
        case EVENT_WHEEL_CLOCKWISE: {
            if (m_currentBaudIndex == 8) break;
            lv_obj_set_style_text_color(m_baudStateUI.labels[m_currentBaudIndex], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
            lv_obj_set_style_text_color(m_baudStateUI.labels[++m_currentBaudIndex], lv_color_hex(0xACE62F), LV_PART_MAIN);
            scroll_anim(m_baudStateUI.roller, 100 * m_currentBaudIndex);
            break;
        }

        case EVENT_WHEEL_COUNTERCLOCKWISE: {
            if (m_currentBaudIndex == 0) break;
            lv_obj_set_style_text_color(m_baudStateUI.labels[m_currentBaudIndex], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
            lv_obj_set_style_text_color(m_baudStateUI.labels[--m_currentBaudIndex], lv_color_hex(0xACE62F), LV_PART_MAIN);
            scroll_anim(m_baudStateUI.roller, 100 * m_currentBaudIndex);
            break;
        }

        case EVENT_BUTTON_PRESS: {
            const ButtonEvent* buttonEvent = static_cast<const ButtonEvent*>(event);
            if (buttonEvent->getButtonId() == BOOT_BTN) {
                int stateId = FunctionUartState::ID;
                State* nextState = StateManager::getInstance()->getState(stateId);
                if (nextState) {
                    m_exit = true;
                    changeBaudRate();
                    machine->requestDisplayUpdate();
                    machine->changeState(nextState);
                    break;
                }
            }
            return false;
        }

        case EVENT_BUTTON_LONGPRESS: {
            const ButtonEvent* buttonEvent = static_cast<const ButtonEvent*>(event);
            if (buttonEvent->getButtonId() == BOOT_BTN) {
                int stateId = FunctionUartState::ID;
                State* nextState = StateManager::getInstance()->getState(stateId);
                if (nextState) {
                    m_exit = true;
                    machine->requestDisplayUpdate();
                    machine->changeState(nextState);
                    break;
                }
            }
            return false;
        }

        default:
            return false;
    }

    return true;
}

void FunctionBaudState::updateDisplay(DisplayContext* display)
{
    if (!display) {
        return;
    }

    static bool background = true;
    static int lastTime = millis();

    if (m_exit) {
        background = false;
    }
    display->updateBaudLED(m_currentLedIndex, background);

    if (millis() - lastTime >= 1000) {
        background = !background;
        lastTime = millis();
    }
}

void scroll_x_anim(void * obj, int32_t v)
{
    lv_obj_scroll_to_x((lv_obj_t*)obj, v, LV_ANIM_OFF);
}

void FunctionBaudState::scroll_anim(lv_obj_t* obj, int32_t v)
{
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, obj);
    lv_anim_set_duration(&anim, 100);

    lv_anim_set_values(&anim, lv_obj_get_scroll_x(obj), v);
    lv_anim_set_exec_cb(&anim, scroll_x_anim);
    lv_anim_set_path_cb(&anim, lv_anim_path_linear);
    lv_anim_start(&anim);
}

void FunctionBaudState::changeBaudRate()
{
    m_baudRate = m_baudRateList[m_currentBaudIndex];
    m_currentLedIndex = m_currentBaudIndex;

    ShowSerial.end();
    COMSerial.end();
    ShowSerial.begin(m_baudRate);
    COMSerial.begin(m_baudRate);
}

int FunctionBaudState::getID() const
{
    return ID;
}

const char* FunctionBaudState::getName() const
{
    return "FunctionBaudState";
}

uint FunctionBaudState::m_baudRate = 9600;
