#include "FreeRTOS.h"
#include "task.h"
#include "StateMachine.h"
#include "StateManager.h"
#include "MenuStates.h"
#include "InputTask.h"
#include "DisplayContext.h"
#include "ErrorState.h"
#include "FunctionUartState.h"
#include "FunctionBaudState.h"
#include "FunctionPowerState.h"

#include "DapLink.h"
#include "Global.h"
#include "Tool.h"
#include "LvglStyle.h"

#include <Adafruit_INA228.h>

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// 创建显示上下文
DisplayContext displayContext;

// 创建状态机
StateMachine stateMachine;

// 创建输入任务
InputTask inputTask;

Adafruit_INA228 ina228;

// 错误处理回调
void appErrorHandler(int errorCode, const char* errorMsg) {
    // 记录错误到日志
    // 也可以通过UART发送错误信息
}

static uint32_t my_tick(void) {
    return millis();
}

void initSerial() {
    COMSerial.begin(FunctionBaudState::m_baudRate);

    pinMode(UART_SWITCH, OUTPUT);
    digitalWrite(UART_SWITCH, LOW);
}

void initLED() {
    pinMode(LED_DATA, OUTPUT);
    pinMode(LED_CLOCK, OUTPUT);
    pinMode(LED_LATCH, OUTPUT);

    displayContext.updateBaudLED(1, false);
}

void initLVGL() {
    lv_init();

    lv_tick_set_cb(my_tick);

    lv_display_t* disp;
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);

    static lv_style_t style_screen;
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_hex(0x000000));

    lv_obj_add_style(lv_scr_act(), &style_screen, 0);

    lv_timer_handler();
}

void initINA228() {
    pinMode(MOS1_PIN, INPUT);
    pinMode(MOS2_PIN, INPUT);

    ina228 = Adafruit_INA228();

    Wire.setPins(INA_I2C_SDA, INA_I2C_SCL);
    Wire.setClock(INA_I2C_FREQUENCY);

    if (!ina228.begin(INA_I2C_ADDR)) {
        ShowSerial.println("Couldn't find INA228 chip");
        return;
    }

    // set shunt resistance and max current
    ina228.setShunt(0.068, 1.0);
    ina228.setAveragingCount(INA228_COUNT_16);

    // set the time over which to measure the current and bus voltage
    ina228.setVoltageConversionTime(INA228_TIME_150_us);
    ina228.setCurrentConversionTime(INA228_TIME_280_us);
}

void setup() {
    // 硬件初始化
    // TODO: 初始化MCU外设、显示屏等
    initSerial();
    initLED();
    initLVGL();
    initStyle();
    initDapLink();
    ShowSerial.begin(FunctionBaudState::m_baudRate);
    initINA228();
    initValueFromEEPROM();
    pinMode(BOOT_BTN, INPUT_PULLUP);
    pinMode(ENCODER_PINA, INPUT);
    pinMode(ENCODER_PINB, INPUT);

    // 注册状态
    StateManager* stateManager = StateManager::getInstance();

    // 创建并注册主菜单状态
    MainMenuState* mainMenu = new MainMenuState();
    FunctionUartState* uartState = new FunctionUartState();
    FunctionBaudState* baudState = new FunctionBaudState();
    FunctionPowerState* powerState = new FunctionPowerState();

    // 添加菜单项
    mainMenu->addMenuItem("Function Uart", FunctionUartState::ID);
    mainMenu->addMenuItem("Function Power", FunctionPowerState::ID);
    stateManager->registerState(mainMenu);

    // 注册功能状态
    stateManager->registerState(uartState);
    stateManager->registerState(baudState);
    stateManager->registerState(powerState);
    // TODO: 注册其他功能状态...

    // 创建错误状态
    ErrorState* errorState = new ErrorState();
    stateManager->registerState(errorState);

    // 设置错误处理器
    stateMachine.setErrorHandler(appErrorHandler);

    displayContext.setINA228(&ina228);

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

    ShowSerial.printf("All settings are successful\n");
}

void loop()
{
}
