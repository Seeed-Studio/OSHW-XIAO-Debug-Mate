#ifndef MENU_STATES_H
#define MENU_STATES_H

#include "State.h"
#include "StateMachine.h"
#include "DisplayContext.h"

// 菜单项结构
struct MenuItem {
    const char* label;
    int stateId;
};

// 主菜单状态
class MainMenuState : public State {
private:
    static const int MAX_ITEMS = 10;
    MenuItem m_items[MAX_ITEMS];
    int m_itemCount;
    int m_currentSelection;
    
public:
    enum { ID = 1 };
    
    MainMenuState();
    
    // 添加菜单项
    bool addMenuItem(const char* label, int stateId);
    
    // 实现State接口
    virtual void onEnter();
    virtual void onExit();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
    virtual void updateDisplay(DisplayContext* display);
    virtual int getID() const { return ID; }
    virtual const char* getName() const { return "MainMenu"; }
};

// 功能基类状态
class FunctionState : public State {
protected:
    const char* m_title;
    
public:
    FunctionState(const char* title) : m_title(title) {}
    
    // 共用实现
    virtual void onEnter();
    virtual void onExit();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
};

// 特定功能状态
class Function1State : public FunctionState {
public:
    enum { ID = 2 };
    
    Function1State() : FunctionState("Function 1") {}
    
    // 特定实现
    virtual void updateDisplay(DisplayContext* display);
    virtual int getID() const { return ID; }
    virtual const char* getName() const { return "Function1"; }
};

// 错误状态
class ErrorState : public State {
private:
    int m_errorCode;
    const char* m_errorMessage;
    
public:
    enum { ID = 0 };
    
    ErrorState();
    
    void setError(int code, const char* message);
    
    // 实现State接口
    virtual void onEnter();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
    virtual void updateDisplay(DisplayContext* display);
    virtual int getID() const { return ID; }
    virtual const char* getName() const { return "Error"; }
};

#endif // MENU_STATES_H
