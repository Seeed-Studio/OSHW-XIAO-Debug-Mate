#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include "DisplayContext.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define EVENT_QUEUE_SIZE 10
#define MAX_EVENT_SIZE sizeof(WheelEvent) // Use size of the largest event type

typedef void (*ErrorHandler)(int errorCode, const char* errorMsg);

class StateMachine {
private:
    State* m_currentState;
    State* m_previousState;

    State* m_errorState;
    ErrorHandler m_errorHandler;

    SemaphoreHandle_t m_stateMutex;
    DisplayContext* m_displayContext;

    QueueHandle_t m_eventQueue;
    TaskHandle_t m_stateMachineTask;

    // 内部方法
    static void stateMachineTaskFunc(void* params);

public:
    StateMachine();
    ~StateMachine();

    // Initialize the state machine
    bool init(State* initialState, State* errorState = 0);

    // Start state machine task
    bool start(UBaseType_t priority = 1);

    // Stop state machine task
    void stop();

    // Push an event to the queue
    bool postEvent(const Event* event);

    // Handle event (called by task loop)
    bool handleEvent(const Event* event);

    // State transition
    bool changeState(State* newState);

    // Return to previous state
    bool goToPreviousState();

    // Set error handler callback
    void setErrorHandler(ErrorHandler handler);

    // Trigger error handling
    void handleError(int errorCode, const char* errorMsg);

    // Get current state
    State* getCurrentState(); // NOTE: no use now

    // Set display context
    void setDisplayContext(DisplayContext* display);

    // Request display update
    void requestDisplayUpdate(); // NOTE: no use now
};

#endif // STATE_MACHINE_H
