#ifndef STATE_H
#define STATE_H

#include "Event.h"
#include "DisplayContext.h"

class StateMachine;

// 状态接口
class State {
public:
    virtual ~State() {}
    
    // 进入此状态时调用
    virtual void onEnter() {}
    
    // 离开此状态时调用
    virtual void onExit() {}
    
    // 事件处理
    virtual bool handleEvent(StateMachine* machine, const Event* event) = 0;
    
    // 更新显示
    virtual void updateDisplay(DisplayContext* display) = 0;
    
    // 状态ID
    virtual int getID() const = 0;
    
    // 状态名称，用于调试
    virtual const char* getName() const = 0;
};

#endif // STATE_H
