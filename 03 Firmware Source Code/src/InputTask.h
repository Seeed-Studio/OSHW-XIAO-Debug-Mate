#ifndef INPUT_TASK_H
#define INPUT_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "StateMachine.h"

// Enumerate button actions
enum ButtonAction {
    NoneAction,
    ButtonRelease,
    ButtonShortPress,
    ButtonLongPress
};

class InputTask {
private:
    TaskHandle_t m_wheelTask;
    TaskHandle_t m_buttonTask;
    StateMachine* m_stateMachine;
    
    static void wheelTaskFunc(void* params);
    static void buttonTaskFunc(void* params);

public:
    static ButtonAction m_buttonAction;
    
public:
    InputTask();
    ~InputTask();
    
    // Set state machine reference
    void setStateMachine(StateMachine* machine);
    
    // Start input tasks
    bool start(UBaseType_t priority = 2);
    
    // Stop input tasks
    void stop();

    // Button interrupt handler
    static void btnInterruptHandler(void);
};

#endif // INPUT_TASK_H
