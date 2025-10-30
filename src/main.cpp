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
#include "frame.h"

#include <Adafruit_INA228.h>

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// Create display context
DisplayContext displayContext;

// Create state machine instance
StateMachine stateMachine;

// Create input task instance
InputTask inputTask;

Adafruit_INA228 ina228;

// Error handler callback
void appErrorHandler(int errorCode, const char* errorMsg) {
    // Log error (optionally send via UART)
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

    displayContext.updateBaudLED(1, true);
}

void animBootCompleted(lv_anim_t* anim) {
    stateMachine.setBootCompleted();
}

void initAnimBoot(lv_obj_t* scr) {
    lv_obj_t* animimg = lv_animimg_create(scr);
    lv_obj_center(animimg);
    lv_animimg_set_src(animimg, (const void **) anim_boot_imgs, BOOT_FRAME_SIZE);
    lv_animimg_set_duration(animimg, 4850);
    lv_animimg_set_repeat_count(animimg, 1);
    lv_animimg_set_completed_cb(animimg, animBootCompleted);
    lv_animimg_start(animimg);
}

static void bootTaskFunc(void* params) {
    initAnimBoot(lv_scr_act());

    while (true) {
        if (stateMachine.getBootCompleted()) {
            vTaskDelete(NULL);
        }

        lv_timer_handler();
        vTaskDelay(30);
    }
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

    xTaskCreate(
        bootTaskFunc,
        "boot Task Func",
        8192,
        nullptr,
        1,
        nullptr
    );

    while (true) {
        if (stateMachine.getBootCompleted()) {
            break;
        }
        delay(100);
    }
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
    // Hardware initialization
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
    ShowSerial.setDebugOutput(true);

    // Register states
    StateManager* stateManager = StateManager::getInstance();

    // Create and register main menu state
    MainMenuState* mainMenu = new MainMenuState();
    FunctionUartState* uartState = new FunctionUartState();
    FunctionBaudState* baudState = new FunctionBaudState();
    FunctionPowerState* powerState = new FunctionPowerState();

    // Add menu items
    mainMenu->addMenuItem("Function Uart", FunctionUartState::ID);
    mainMenu->addMenuItem("Function Power", FunctionPowerState::ID);
    stateManager->registerState(mainMenu);

    // Register functional states
    stateManager->registerState(uartState);
    stateManager->registerState(baudState);
    stateManager->registerState(powerState);
    // TODO: Register other functional states...

    // Create error state
    ErrorState* errorState = new ErrorState();
    stateManager->registerState(errorState);

    // Set error handler
    stateMachine.setErrorHandler(appErrorHandler);

    displayContext.setINA228(&ina228);

    // Set display context
    stateMachine.setDisplayContext(&displayContext);

    // Initialize state machine: main menu as initial state, error state for exception handling
    if (!stateMachine.init(mainMenu, errorState)) {
    // Handle initialization failure
        while(1) {
            ShowSerial.printf("StateMachine init failed here\n");
            delay(100);
        }
    }

    inputTask.setStateMachine(&stateMachine);

    // Start state machine task
    if (!stateMachine.start(1)) {
    // Handle start failure
        while(1) {
            ShowSerial.printf("StateMachine start failed here\n");
            delay(100);
        }
    }

    // Start input task
    if (!inputTask.start(2)) {
    // Handle input task start failure
        stateMachine.stop();
        while(1) {
            ShowSerial.printf("InputTask start failed here\n");
            delay(100);
        }
    }

    ShowSerial.printf("All settings are successful\n");
}

void loop()
{
}
