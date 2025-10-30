#include "StateMachine.h"
#include <string.h> // For memcpy

#include <Arduino.h>

StateMachine::StateMachine() 
    : m_currentState(nullptr), 
      m_previousState(nullptr), 
      m_errorState(nullptr), 
      m_errorHandler(nullptr),
      m_stateMutex(nullptr), // NOTE: need check
      m_displayContext(nullptr),
      m_eventQueue(nullptr), // NOTE: need check
      m_stateMachineTask(nullptr),
      m_isBootCompleted(false)
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

    // Create mutex to protect state access
    m_stateMutex = xSemaphoreCreateMutex();
    if (!m_stateMutex) {
        return false;
    }

    // Create event queue
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

    // Create state machine task
    BaseType_t result = xTaskCreate(
    stateMachineTaskFunc,    // Task function
    "StateMachine",          // Task name
    8192,                    // Stack size (adjust as needed)
    this,                    // Parameter passed to the task
    priority,                // Task priority
    &m_stateMachineTask      // Task handle
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

    while (!machine->m_isBootCompleted) {
        vTaskDelay(30);
    }

    // Call onEnter of the initial state first
    if (xSemaphoreTake(machine->m_stateMutex, (TickType_t) 10) == pdTRUE) {
        State* initialState = machine->m_currentState;
        xSemaphoreGive(machine->m_stateMutex);

        try {
            initialState->onEnter();
            // Initial display update
            if (machine->m_displayContext) {
                initialState->updateDisplay(machine->m_displayContext);
            }
        } catch(...) {
            machine->handleError(1, "Exception in initial state");
        }
    }

    uint8_t eventBuffer[MAX_EVENT_SIZE];

    for (;;) {
    // Wait for an event from the queue
        // if (xQueueReceive(machine->m_eventQueue, eventBuffer, portMAX_DELAY) == pdTRUE) {
        if (xQueueReceive(machine->m_eventQueue, eventBuffer, (TickType_t) 100) == pdTRUE) {
            Event* event = reinterpret_cast<Event*>(eventBuffer);

            // Process event
            machine->handleEvent(event);
            continue;
        }

        if (machine->m_displayContext) {
            machine->m_currentState->updateDisplay(machine->m_displayContext);
        }

        lv_timer_handler(); /* let the GUI do its work */

        vTaskDelay(pdMS_TO_TICKS(30));
    }
}

bool StateMachine::postEvent(const Event* event) {
    if (!event || !m_eventQueue) {
        return false;
    }

    // Copy event into temporary buffer
    uint8_t eventBuffer[MAX_EVENT_SIZE];
    memcpy(eventBuffer, event, MAX_EVENT_SIZE);

    // Send to the queue without waiting (return immediately)
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
    static EventType lastType = EVENT_NONE;
    static uint32_t lastTime = 0;

    if (lastType == event->getType() && (millis() - lastTime) < 60) {
        return false;
    }

    lastType = event->getType();
    lastTime = millis();

    try {
        handled = state->handleEvent(this, event);

    // Update display (if event is handled and causes state change)
        if (handled && m_displayContext) {
            if (xSemaphoreTake(m_stateMutex, portMAX_DELAY) == pdTRUE) {
                State* currentState = m_currentState;
                xSemaphoreGive(m_stateMutex);

                currentState->updateDisplay(m_displayContext);
                lv_timer_handler();
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

    // Check if a state transition is actually needed
    if (newState == m_currentState) {
        xSemaphoreGive(m_stateMutex);
    return true; // Already the target state
    }

    State* oldState = m_currentState;
    m_previousState = oldState;
    m_currentState = newState;

    xSemaphoreGive(m_stateMutex);

    try {
    // Exit old state
        oldState->onExit();

    // Enter new state
        newState->onEnter();

    // Update display
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
    // Invoke error handler callback
    if (m_errorHandler) {
        m_errorHandler(errorCode, errorMsg);
    }

    // If error state exists, switch to it
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

void StateMachine::requestDisplayUpdate() {
    if (!m_displayContext) {
        return;
    }

    State* state = getCurrentState();
    if (state) {
        state->updateDisplay(m_displayContext);
        lv_timer_handler();
    }
}

void StateMachine::setBootCompleted() {
    m_isBootCompleted = true;
}

bool StateMachine::getBootCompleted() {
    return m_isBootCompleted;
}
