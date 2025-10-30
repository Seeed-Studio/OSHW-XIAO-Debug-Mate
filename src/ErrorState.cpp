#include "ErrorState.h"

// ErrorState implementation
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
    // Log error information
}

bool ErrorState::handleEvent(StateMachine* machine, const Event* event) {
    if (!machine || !event) {
        return false;
    }

    // Any button press returns to main menu
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
