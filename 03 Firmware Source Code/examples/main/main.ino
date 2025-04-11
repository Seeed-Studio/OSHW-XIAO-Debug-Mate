#include "FreeRTOS.h"
#include "task.h"
#include "StateMachine.h"
#include "StateManager.h"
#include "MenuStates.h"
#include "InputTask.h"
#include "DisplayContext.h"

#include <TFT_eSPI.h>
#include <SPI.h>
#include "Free_Fonts.h"

#include "DapLink.h"
#include "Global.h"

// 创建显示上下文
DisplayContext displayContext;

// 创建状态机
StateMachine stateMachine;

// 创建输入任务
InputTask inputTask;

TFT_eSPI tft = TFT_eSPI();

// 错误处理回调
void appErrorHandler(int errorCode, const char* errorMsg) {
    // 记录错误到日志
    // 也可以通过UART发送错误信息
}

void initLCD() {
    tft.init();
    tft.setRotation(1);
    displayContext.setTft(&tft);
    displayContext.refresh();
}

void setup() {
    Serial.begin(9600);

    // 硬件初始化
    // TODO: 初始化MCU外设、显示屏等
    initDapLink();
    initLCD();
    pinMode(BOOT_BTN, INPUT_PULLUP);

    // 注册状态
    StateManager* stateManager = StateManager::getInstance();

    // 创建并注册主菜单状态
    MainMenuState* mainMenu = new MainMenuState();
    // 添加菜单项
    mainMenu->addMenuItem("Function 1", Function1State::ID);
    mainMenu->addMenuItem("Function 2", 3); // 假设Function2State的ID是3
    mainMenu->addMenuItem("Function 3", 4); // 假设Function3State的ID是4
    stateManager->registerState(mainMenu);

    // 注册功能状态
    stateManager->registerState(new Function1State());
    // TODO: 注册其他功能状态...

    // 创建错误状态
    ErrorState* errorState = new ErrorState();
    stateManager->registerState(errorState);

    // 设置错误处理器
    stateMachine.setErrorHandler(appErrorHandler);

    // 设置显示上下文
    stateMachine.setDisplayContext(&displayContext);

    // 初始化状态机，以主菜单为初始状态，错误状态为异常处理状态
    if (!stateMachine.init(mainMenu, errorState)) {
        // 初始化失败处理
        while(1); // 或者重启系统
    }

    inputTask.setStateMachine(&stateMachine);

    // 启动状态机任务
    if (!stateMachine.start(1)) {
        // 启动失败处理
        while(1);
    }

    // 启动输入任务
    if (!inputTask.start(2)) {
        // 启动失败处理
        stateMachine.stop();
        while(1);
    }

    Serial.printf("All settings are successful\n");
}

void loop()
{
}
