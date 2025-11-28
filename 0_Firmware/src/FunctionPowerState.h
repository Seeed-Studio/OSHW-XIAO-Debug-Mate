#ifndef FUNCTION_POWER_STATE_H
#define FUNCTION_POWER_STATE_H

#include "Global.h"
#include "LvglStyle.h"
#include "MenuStates.h"
#include "FunctionUartState.h"

#define POWER_INTERFACE_SIMPLE   0
#define POWER_INTERFACE_MEDIUM   1
#define POWER_INTERFACE_COMPLEX  2

#define POWER_REFRESH_TIME       168

struct POWER_STATE_SIMPLE_T {
    lv_obj_t* voltage;
    lv_obj_t* current;
    lv_obj_t* power;
};

struct POWER_STATE_MEDIUM_T {
    lv_obj_t* voltage;
    lv_obj_t* current_A;
    lv_obj_t* current_mA;
    lv_obj_t* current_uA;
    lv_obj_t* power_W;
    lv_obj_t* power_mW;
};

struct POWER_STATE_COMPLEX_T {
    lv_obj_t* voltage;
    lv_obj_t* current;
    lv_obj_t* power;

    lv_obj_t* viewGroup;
    lv_obj_t* minCurrent_A;
    lv_obj_t* minPower_W;
    lv_obj_t* maxCurrent_A;
    lv_obj_t* maxPower_W;
    lv_obj_t* totalCurrent_Ah;
    lv_obj_t* totalPower_Wh;

    lv_obj_t* time;
};

struct POWER_STATE_UI_T {
    lv_obj_t* Screen;
    lv_obj_t* powerGroup[3];

    POWER_STATE_SIMPLE_T powerSimple;
    POWER_STATE_MEDIUM_T powerMedium;
    POWER_STATE_COMPLEX_T powerComplex;
};

class FunctionPowerState : public FunctionState {
public:
    enum { ID = 4 };

    FunctionPowerState();
    void createPowerSimpleUI();
    void createPowerMediumUI();
    void createPowerComplexUI();

    void onEnter() override;
    void onExit() override;
    bool handleEvent(StateMachine* machine, const Event* event) override;
    void updateDisplay(DisplayContext* display) override;
    int getID() const override;
    const char* getName() const override;

private:
    POWER_STATE_UI_T m_powerStateUI;
    unsigned long m_startTime;
    unsigned long m_lastTime;
    unsigned long wheelLastInterruptTime;
    int m_currentIndex;
    int m_update;

    float m_voltage;
    float m_current;
    float m_minCurrent;
    float m_maxCurrent;
    float m_totalCurrent;
    float m_power;
    float m_minPower;
    float m_maxPower;
    float m_totalPower;
};

#endif // FUNCTION_POWER_STATE_H
