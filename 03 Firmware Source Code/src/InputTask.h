#ifndef INPUT_TASK_H
#define INPUT_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "StateMachine.h"

class InputTask {
private:
    TaskHandle_t m_wheelTask;
    TaskHandle_t m_buttonTask;
    TaskHandle_t m_touchTask;
    StateMachine* m_stateMachine;
    
    static void wheelTaskFunc(void* params);
    static void buttonTaskFunc(void* params);
    static void touchTaskFunc(void* params);
    
public:
    InputTask();
    ~InputTask();
    
    // 设置状态机引用
    void setStateMachine(StateMachine* machine);
    
    // 启动输入任务
    bool start(UBaseType_t priority = 2);
    
    // 停止输入任务
    void stop();
};

#endif // INPUT_TASK_H
