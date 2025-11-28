#ifndef FUNCTIONUARTSTATE_H
#define FUNCTIONUARTSTATE_H

#include "Global.h"
#include "LvglStyle.h"
#include "MenuStates.h"
#include "StateManager.h"
#include "FunctionBaudState.h"

#define UART_DATA_SIZE 50


struct UartStateUI {
    lv_obj_t* Screen;
    lv_obj_t* UartTypeBg;
    lv_obj_t* UartBaudBg;
    lv_obj_t* UartRxBg;
    lv_obj_t* UartTxBg;
    lv_obj_t* UartRxLEDGroup;
    lv_obj_t* UartTxLEDGroup;
    lv_obj_t* UartRxGroup;
    lv_obj_t* UartTxGroup;

    lv_obj_t* UartTypeLabel;
    lv_obj_t* UartBaudLabel;
    lv_obj_t* UartBaudLine;
    lv_obj_t* UartRxLedLeftList[5];
    lv_obj_t* UartRxLedRightList[5];
    lv_obj_t* UartTxLedLeftList[5];
    lv_obj_t* UartTxLedRightList[5];
    lv_obj_t* UartRxLed;
    lv_obj_t* UartTxLed;
    lv_obj_t* UartRxTextArea;
    lv_obj_t* UartTxTextArea;
};

// Enumerate UART types
enum UartType{
    UART_TYPE_XIAO,
    UART_TYPE_Grove
};

// Specific function state for UART feature
class FunctionUartState : public FunctionState {
private:
    UartType m_uartType;
    UartStateUI m_uartStateUI;
    TaskHandle_t m_uartTask;
    QueueHandle_t m_rxQueue;
    QueueHandle_t m_txQueue;
    int m_isUartInfoDisplay;
    int m_currentSelection;

    static void uartTaskFunc(void* params);
    void createOptionBarUI();
    void createLedUI();
    void createMessageUI();

public:
    enum { ID = 2 };

    FunctionUartState();
    void onEnter() override;
    void onExit() override;
    // Specific implementation
    void updateLedEffect();
    void updateDisplay(DisplayContext* display) override;
    int getID() const override;
    const char* getName() const override;

    void changeUartType();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
};

#endif //FUNCTIONUARTSTATE_H
