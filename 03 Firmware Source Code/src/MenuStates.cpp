#include "MenuStates.h"
#include "StateManager.h"

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
    
    display->lock();
    
    // 清屏
    display->clear();
    
    // 绘制标题
    display->drawText(10, 10, "Main Menu", true);
    
    // 绘制菜单项
    for (int i = 0; i < m_itemCount; ++i) {
        if (i == m_currentSelection) {
            // 高亮当前选中项
            display->drawRect(5, 30 + i * 20, 230, 18, true);
            display->drawText(10, 32 + i * 20, m_items[i].label, true);
        } else {
            display->drawText(10, 32 + i * 20, m_items[i].label, false);
        }
    }
    
    // 刷新显示
    display->refresh();
    
    display->unlock();
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
