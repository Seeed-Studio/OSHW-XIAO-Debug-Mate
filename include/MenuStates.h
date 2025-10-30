#ifndef MENU_STATES_H
#define MENU_STATES_H

#include "State.h"
#include "StateMachine.h"
#include "DisplayContext.h"

// Menu item structure
struct MenuItem {
    const char* label;
    int stateId;
};

struct MAIN_MENU_T {
    lv_obj_t* screen;
    lv_obj_t* uart_bg;
    lv_obj_t* power_bg;
    lv_obj_t* baudRate;
    lv_obj_t* ledTitle;
    lv_obj_t* ledRx;
    lv_obj_t* ledTx;
    lv_obj_t* vol;
    lv_obj_t* cur;
    lv_obj_t* power;
};

// Main menu state
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
    
    // Add a menu item
    bool addMenuItem(const char* label, int stateId);
    
    // Implement State interface
    virtual void onEnter();
    virtual void onExit();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
    virtual void updateDisplay(DisplayContext* display);
    virtual int getID() const { return ID; }
    virtual const char* getName() const { return "MainMenu"; }
};

// Functional base state
class FunctionState : public State {
protected:
    const char* m_title;
    
public:
    FunctionState(const char* title) : m_title(title) {}
    
    // Shared implementation
    virtual void onEnter();
    virtual void onExit();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
};

#endif // MENU_STATES_H
