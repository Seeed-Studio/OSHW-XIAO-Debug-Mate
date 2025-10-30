#include "StateManager.h"

StateManager* StateManager::s_instance = nullptr;

StateManager::StateManager() {
    for (int i = 0; i < MAX_STATES; ++i) {
        m_states[i] = nullptr;
    }
}

StateManager::~StateManager() {
}

StateManager* StateManager::getInstance() {
    if (!s_instance) {
        s_instance = new StateManager();
    }
    return s_instance;
}

void StateManager::releaseInstance() {
    if (!s_instance) {
        return;
    }
    delete s_instance;
    s_instance = nullptr;
}

bool StateManager::registerState(State* state) {
    if (!state) {
        return false;
    }

    int id = state->getID();
    if (id < 0 || id >= MAX_STATES) {
        return false;
    }

    // 已存在则替换
    if (m_states[id]) {
        delete m_states[id];
    }

    m_states[id] = state;
    return true;
}

State* StateManager::getState(int stateId) const {
    if (stateId < 0 || stateId >= MAX_STATES) {
        return nullptr;
    }
    return m_states[stateId];
}

int StateManager::getStateCount() const {
    int count = 0;
    for (int i = 0; i < MAX_STATES; ++i) {
        if (m_states[i]) {
            ++count;
        }
    }
    return count;
}
