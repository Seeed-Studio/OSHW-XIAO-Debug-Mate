#include "StateMachine.h"
#include <string.h> // 用于memcpy

#include <Arduino.h>

StateMachine::StateMachine() 
    : m_currentState(nullptr), 
      m_previousState(nullptr), 
      m_errorState(nullptr), 
      m_errorHandler(nullptr),
      m_stateMutex(nullptr), // NOTE: need check
      m_displayContext(nullptr),
      m_eventQueue(nullptr), // NOTE: need check
      m_stateMachineTask(nullptr)
{
}

StateMachine::~StateMachine() {
    stop();

    if (m_stateMutex) {
        vSemaphoreDelete(m_stateMutex);
    }

    if (m_eventQueue) {
        vQueueDelete(m_eventQueue);
    }
}

bool StateMachine::init(State* initialState, State* errorState) {
    if (!initialState) {
        return false;
    }

    // 创建互斥锁保护状态访问
    m_stateMutex = xSemaphoreCreateMutex();
    if (!m_stateMutex) {
        return false;
    }

    // 创建事件队列
    m_eventQueue = xQueueCreate(EVENT_QUEUE_SIZE, MAX_EVENT_SIZE); // NOTE: need check max size
    if (!m_eventQueue) {
        vSemaphoreDelete(m_stateMutex);
        m_stateMutex = 0;
        return false;
    }

    m_currentState = initialState;
    m_errorState = errorState;

    return true;
}

bool StateMachine::start(UBaseType_t priority) {
    if (!m_currentState || !m_eventQueue || !m_stateMutex) {
        return false;
    }

    // 创建状态机任务
    BaseType_t result = xTaskCreate(
        stateMachineTaskFunc,    // 任务函数
        "StateMachine",          // 任务名称
        4096,                    // 堆栈大小，根据实际需求调整
        this,                    // 传递给任务的参数
        priority,                // 任务优先级
        &m_stateMachineTask      // 任务句柄
    );

    if (result != pdPASS) {
        return false;
    }

    return true;
}

void StateMachine::stop() {
    if (m_stateMachineTask) {
        vTaskDelete(m_stateMachineTask);
        m_stateMachineTask = nullptr;
    }
}

void StateMachine::stateMachineTaskFunc(void* params) {
    StateMachine* machine = static_cast<StateMachine*>(params);

    // 先调用当前状态的onEnter
    if (xSemaphoreTake(machine->m_stateMutex, (TickType_t) 10) == pdTRUE) {
        State* initialState = machine->m_currentState;
        xSemaphoreGive(machine->m_stateMutex);

        try {
            initialState->onEnter();
            // 初始更新显示
            if (machine->m_displayContext) {
                initialState->updateDisplay(machine->m_displayContext);
            }
        } catch(...) {
            machine->handleError(1, "Exception in initial state");
        }
    }

    uint8_t eventBuffer[MAX_EVENT_SIZE];

    for (;;) {
        Serial.printf("[%s]::%d - main loop\n", __func__, __LINE__);
        // 等待事件队列
        if (xQueueReceive(machine->m_eventQueue, eventBuffer, portMAX_DELAY) == pdTRUE) {
            Event* event = reinterpret_cast<Event*>(eventBuffer);

            // 处理事件
            machine->handleEvent(event);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

bool StateMachine::postEvent(const Event* event) {
    if (!event || !m_eventQueue) {
        return false;
    }

    // 复制事件到临时缓冲区
    uint8_t eventBuffer[MAX_EVENT_SIZE];
    memcpy(eventBuffer, event, MAX_EVENT_SIZE);

    // 发送到队列，不等待（立即返回）
    BaseType_t result = xQueueSendToBack(m_eventQueue, eventBuffer, 0);
    return (result == pdTRUE);
}

bool StateMachine::handleEvent(const Event* event) {
    if (!event) {
        return false;
    }

    if (xSemaphoreTake(m_stateMutex, portMAX_DELAY) != pdTRUE) {
        return false;
    }

    State* state = m_currentState;
    xSemaphoreGive(m_stateMutex);

    bool handled = false;

    try {
        handled = state->handleEvent(this, event);

        // 更新显示（如果事件被处理且导致了状态变化）
        if (handled && m_displayContext) {
            if (xSemaphoreTake(m_stateMutex, portMAX_DELAY) == pdTRUE) {
                State* currentState = m_currentState;
                xSemaphoreGive(m_stateMutex);

                currentState->updateDisplay(m_displayContext);
            }
        }
    } catch(...) {
        handleError(2, "Exception in event handling");
        return false;
    }

    return handled;
}

bool StateMachine::changeState(State* newState) {
    if (!newState) {
        return false;
    }

    if (xSemaphoreTake(m_stateMutex, portMAX_DELAY) != pdTRUE) {
        return false;
    }

    // 检查是否实际需要状态变化
    if (newState == m_currentState) {
        xSemaphoreGive(m_stateMutex);
        return true; // 已经是目标状态
    }

    State* oldState = m_currentState;
    m_previousState = oldState;
    m_currentState = newState;

    xSemaphoreGive(m_stateMutex);

    try {
        // 退出旧状态
        oldState->onExit();

        // 进入新状态
        newState->onEnter();

        // 更新显示
        if (m_displayContext) {
            newState->updateDisplay(m_displayContext);
        }

        return true;
    } catch(...) {
        handleError(3, "Exception during state transition");
        return false;
    }
}

bool StateMachine::goToPreviousState() {
    if (xSemaphoreTake(m_stateMutex, portMAX_DELAY) != pdTRUE) {
        return false;
    }

    State* prevState = m_previousState;
    xSemaphoreGive(m_stateMutex);

    if (!prevState) {
        return false;
    }

    return changeState(prevState);
}

void StateMachine::setErrorHandler(ErrorHandler handler) {
    m_errorHandler = handler;
}

void StateMachine::handleError(int errorCode, const char* errorMsg) {
    // 调用错误处理器
    if (m_errorHandler) {
        m_errorHandler(errorCode, errorMsg);
    }

    // 如果有错误状态，切换到错误状态
    if (m_errorState && xSemaphoreTake(m_stateMutex, portMAX_DELAY) == pdTRUE) {
        if (m_currentState != m_errorState) {
            State* errorState = m_errorState;
            xSemaphoreGive(m_stateMutex);
            changeState(errorState);
        } else {
            xSemaphoreGive(m_stateMutex);
        }
    }
}

State* StateMachine::getCurrentState() {
    State* result = 0;

    if (xSemaphoreTake(m_stateMutex, portMAX_DELAY) == pdTRUE) {
        result = m_currentState;
        xSemaphoreGive(m_stateMutex);
    }

    return result;
}

void StateMachine::setDisplayContext(DisplayContext* display) {
    m_displayContext = display;
}

DisplayContext* StateMachine::getDisplayContext() {
    return m_displayContext;
}

void StateMachine::requestDisplayUpdate() {
    if (!m_displayContext) {
        return;
    }

    State* state = getCurrentState();
    if (state) {
        state->updateDisplay(m_displayContext);
    }
}
