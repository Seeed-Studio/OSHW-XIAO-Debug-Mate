#ifndef FUNCTION_BAUD_STATE_H
#define FUNCTION_BAUD_STATE_H

#include "MenuStates.h"
#include "Global.h"
#include "LvglStyle.h"
#include "StateManager.h"
#include "FunctionPowerState.h"

#define NUM_BAUDRATES 9

struct BAUD_STATE_UI_T {
    lv_obj_t* screen;
    lv_obj_t* roller;
    lv_obj_t* labels[NUM_BAUDRATES];
};

// Specific function state (Baud rate configuration)
class FunctionBaudState : public FunctionState {
public:
    enum { ID = 3 };

    FunctionBaudState();

    // Specific implementation
    virtual void updateDisplay(DisplayContext* display);
    void scroll_anim(lv_obj_t* obj, int32_t v);
    void changeBaudRate();
    int getID() const override;
    const char* getName() const override;
    void onEnter() override;
    void onExit() override;
    bool handleEvent(StateMachine* machine, const Event* event) override;

public:
    static uint m_baudRate;
private:
    BAUD_STATE_UI_T m_baudStateUI;
    uint m_baudRateList[NUM_BAUDRATES] = {4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
    uint8_t m_currentBaudIndex;
    uint8_t m_currentLedIndex;
    bool m_exit;
};

#endif // FUNCTION_BAUD_STATE_H
