#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"

#define MAX_STATES 20  // 最大状态数

class StateManager {
private:
    static StateManager* s_instance;
    State* m_states[MAX_STATES];  // 状态数组

    // 私有构造函数，实现单例模式
    StateManager();
    
public:
    ~StateManager();

    // 获取单例实例
    static StateManager* getInstance();

    // 释放单例
    static void releaseInstance();

    // 注册状态
    bool registerState(State* state);

    // 获取状态
    State* getState(int stateId) const;

    // 状态数量
    int getStateCount() const;
};

#endif // STATE_MANAGER_H
