#ifndef INPUT_TASK_H
#define INPUT_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "StateMachine.h"

// 枚举按键动作
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
    
    // 设置状态机引用
    void setStateMachine(StateMachine* machine);
    
    // 启动输入任务
    bool start(UBaseType_t priority = 2);
    
    // 停止输入任务
    void stop();

    //按钮中断处理函数
    static void btnInterruptHandler(void);
};

#endif // INPUT_TASK_H
