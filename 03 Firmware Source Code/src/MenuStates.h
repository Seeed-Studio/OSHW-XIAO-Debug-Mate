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

struct MAIN_MENU_T {
    lv_obj_t* screen;
    lv_obj_t* uart_bg;
    lv_obj_t* baud_value;
    /* lv_obj_t* led[3]; */
    lv_obj_t* vol;
    lv_obj_t* cur;
    lv_obj_t* power;
};

// 主菜单状态
class MainMenuState : public State {
private:
    static const int MAX_ITEMS = 10;
    MAIN_MENU_T m_mainMenu;
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


#endif // MENU_STATES_H
