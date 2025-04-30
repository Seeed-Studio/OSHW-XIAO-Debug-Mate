//
// Created by Administrator on 25-4-29.
//

#ifndef FUNCTIONUARTSTATE_H
#define FUNCTIONUARTSTATE_H

#include "Global.h"
#include "LvglStyle.h"
#include "MenuStates.h"
#include "FunctionBaudState.h"


struct UartStateUI {
    lv_obj_t* UartScreen;
    lv_obj_t* UartTypeBg;
    lv_obj_t* UartBaudBg;
    lv_obj_t* UartRxBg;
    lv_obj_t* UartTxBg;

    lv_obj_t* UartTypeLabel;
    lv_obj_t* UartBaudLabel;
    lv_obj_t* UartRxLabel;
    lv_obj_t* UartTxLabel;
};

// 枚举串口类型
enum UartType{
    UART_TYPE_XIAO,
    UART_TYPE_Grove
};

// 特定功能状态
class FunctionUartState : public FunctionState {
public:
    enum { ID = 2 };

    FunctionUartState();
    void onEnter() override;
    void onExit() override;
    // 特定实现
    void updateDisplay(DisplayContext* display) override;
    int getID() const override;
    const char* getName() const override;

    void changeUartType();
    virtual bool handleEvent(StateMachine* machine, const Event* event);

public:
    char m_rxBuff[20] = "";
    char m_txBuff[20] = "";
private:
    UartType m_uartType;
    UartStateUI m_uartUI;
};


#endif //FUNCTIONUARTSTATE_H
