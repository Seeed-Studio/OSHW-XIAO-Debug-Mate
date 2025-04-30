//
// Created by Administrator on 25-4-29.
//

#ifndef FUNCTIONPOWERSTATE_H
#define FUNCTIONPOWERSTATE_H

#include "Global.h"
#include "LvglStyle.h"
#include "MenuStates.h"


// 特定功能状态
class FunctionPowerState : public FunctionState {
public:
    enum { ID = 4 };

    FunctionPowerState();
    void onEnter() override;
    void onExit() override;

    // 特定实现
    virtual void updateDisplay(DisplayContext* display);
    int getID() const override;
    const char* getName() const override;
    bool handleEvent(StateMachine* machine, const Event* event) override;

    void powerInterface_1();
    void powerInterface_2();
    void powerInterface_3();


private:
    // lv_obj_t *m_titleLabel;
    lv_obj_t *m_voltageLabel_V;
    lv_obj_t *m_currentLabel_A;
    lv_obj_t *m_currentLabel_mA;
    lv_obj_t *m_currentLabel_uA;
    lv_obj_t *m_powerLabel_W;
    lv_obj_t *m_powerLabel_mW;
    lv_obj_t *m_minLabel;
    lv_obj_t *m_maxLabel;
    lv_obj_t *m_totalLabel;
    lv_obj_t *m_timeLabel;

    //电压
    float m_voltage;
    //电流
    float m_current;
    float m_minCurrent;
    float m_maxCurrent;
    float m_totalCurrent;
    //功率
    float m_power;
    float m_minPower;
    float m_maxPower;
    float m_totalPower;
};


#endif //FUNCTIONPOWERSTATE_H
