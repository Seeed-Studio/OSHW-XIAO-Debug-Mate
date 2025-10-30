#include "Global.h"
#include "InputTask.h"
#include "Event.h"

#include <Arduino.h>

// #define INPUT_DEBUG

InputTask::InputTask() 
    : m_wheelTask(0), 
      m_buttonTask(0), 
      m_stateMachine(0)
{
}

InputTask::~InputTask() {
    stop();
}

void InputTask::setStateMachine(StateMachine* machine) {
    m_stateMachine = machine;
}

bool InputTask::start(UBaseType_t priority) {
    if (!m_stateMachine) {
        return false;
    }

    // Create wheel (encoder) task
    BaseType_t result = xTaskCreate(
        wheelTaskFunc,
        "WheelTask",
        4096,
        this,
        priority,
        &m_wheelTask
    );

    if (result != pdPASS) {
        return false;
    }

    // Create button task
    result = xTaskCreate(
        buttonTaskFunc,
        "ButtonTask",
        4096,
        this,
        priority,
        &m_buttonTask
    );

    if (result != pdPASS) {
        vTaskDelete(m_wheelTask);
        m_wheelTask = 0;
        return false;
    }

    return true;
}

void InputTask::stop() {
    if (m_wheelTask) {
        vTaskDelete(m_wheelTask);
        m_wheelTask = 0;
    }

    if (m_buttonTask) {
        vTaskDelete(m_buttonTask);
        m_buttonTask = 0;
    }
}

void InputTask::wheelTaskFunc(void* params) {
    InputTask* inputTask = static_cast<InputTask*>(params);
    StateMachine* stateMachine = inputTask->m_stateMachine;
    EventType encoderSta = EVENT_NONE;
    int encoderA = 0, encoderB = 0;
    static uint cntA       = 0;
    static uint cntB       = 0;
    static uint buffer     = 0;
    static uint status     = 0;
    static uint lastStatus = 0;

    for (;;) {
        encoderA = digitalRead(ENCODER_PINA);
        encoderB = digitalRead(ENCODER_PINB);

        if (encoderA) {
            if (cntA)  cntA--;
            else      status |= 0x01;
        } else {
            if (cntA < 4)  cntA++;
            else        status &= ~0x01;
        }

        if (encoderB) {
            if (cntB)  cntB--;
            else      status |= 0x02;
        } else {
            if (cntB < 4)  cntB++;
            else        status &= ~0x02;
        }

        if (lastStatus != status) {
            lastStatus = status;
            buffer <<= 2;
            buffer |= status;
            if (status == 0x03) {
                if (buffer == 0x87)       encoderSta = EVENT_WHEEL_COUNTERCLOCKWISE;
                else if (buffer == 0x4B)  encoderSta = EVENT_WHEEL_CLOCKWISE;
                buffer = 0;
            }
        }

        if (encoderSta == EVENT_WHEEL_COUNTERCLOCKWISE) {
            encoderSta = EVENT_NONE;

            WheelEvent event(false);
            stateMachine->postEvent(&event);
        } else if (encoderSta == EVENT_WHEEL_CLOCKWISE) {
            encoderSta = EVENT_NONE;

            WheelEvent event(true);
            stateMachine->postEvent(&event);
        }

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void InputTask::buttonTaskFunc(void* params) {
    InputTask* inputTask = static_cast<InputTask*>(params);
    StateMachine* stateMachine = inputTask->m_stateMachine;

    attachInterrupt(digitalPinToInterrupt(BOOT_BTN), InputTask::btnInterruptHandler, CHANGE);

    for (;;) {
        if (m_buttonAction == ButtonAction::ButtonShortPress) {
            m_buttonAction = ButtonAction::NoneAction;
            ButtonEvent event(EVENT_BUTTON_PRESS, BOOT_BTN);
            stateMachine->postEvent(&event);
        } else if (m_buttonAction == ButtonAction::ButtonLongPress) {
            m_buttonAction = ButtonAction::NoneAction;
            ButtonEvent event(EVENT_BUTTON_LONGPRESS, BOOT_BTN);
            stateMachine->postEvent(&event);
        }

    // Button scan delay
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void InputTask::btnInterruptHandler()
{
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();
    static unsigned long pressStartTime = 0;

    // If interrupt interval < 50ms treat as debounce noise
    if (interruptTime - lastInterruptTime > DEBOUNCE_DELAT) {
        lastInterruptTime = interruptTime;
    // Read actual button state
        bool btnState = digitalRead(BOOT_BTN);

        if (btnState == LOW) {
            // Button pressed: record press start time
            pressStartTime = millis();
        } else {
            unsigned long pressDuration = millis() - pressStartTime;
            if (pressDuration < 500) {

                m_buttonAction = ButtonAction::ButtonShortPress;
            } else if (pressDuration >= LONG_PRESS_DELAY) {
                m_buttonAction = ButtonAction::ButtonLongPress;
            } else {
                m_buttonAction = ButtonAction::ButtonRelease;
            }
        }
    }
}

ButtonAction InputTask::m_buttonAction = ButtonAction::NoneAction;

