#include "ErrorState.h"

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

    display->unlock();
}

int ErrorState::getID() const
{
    return ID;
}

const char* ErrorState::getName() const
{
    return "Error";
}
