#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include "DisplayContext.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define EVENT_QUEUE_SIZE 10
#define MAX_EVENT_SIZE sizeof(WheelEvent) // 使用最大的事件类型尺寸

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

    // 初始化状态机
    bool init(State* initialState, State* errorState = 0);

    // 启动状态机任务
    bool start(UBaseType_t priority = 1);

    // 停止状态机任务
    void stop();

    // 推送事件到队列
    bool postEvent(const Event* event);

    // 事件处理（由状态机任务调用）
    bool handleEvent(const Event* event);

    // 状态转换
    bool changeState(State* newState);

    // 返回到前一个状态
    bool goToPreviousState();

    // 设置错误处理器
    void setErrorHandler(ErrorHandler handler);

    // 触发错误处理
    void handleError(int errorCode, const char* errorMsg);

    // 获取当前状态
    State* getCurrentState(); // NOTE: no use now

    // 设置显示上下文
    void setDisplayContext(DisplayContext* display);

    // 请求更新显示
    void requestDisplayUpdate(); // NOTE: no use now
};

#endif // STATE_MACHINE_H
