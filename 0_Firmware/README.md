# 🔧 XIAO Debug Mate Firmware

This directory contains the main firmware source code for the XIAO Debug Mate debugger.

## 📁 Directory Structure

```
0_Firmware/
├── examples/
│   └── main/
│       └── main.ino      # Main Arduino sketch entry point
├── src/                  # Core library source files
│   ├── DapLink.*         # DAPLink debugger implementation
│   ├── StateMachine.*    # State machine framework
│   ├── StateManager.*    # State management
│   ├── MenuStates.*      # Main menu UI states
│   ├── FunctionUartState.*   # UART bridge function
│   ├── FunctionBaudState.*   # Baud rate configuration
│   ├── FunctionPowerState.*  # Power monitoring function
│   ├── InputTask.*       # Encoder and button input handling
│   ├── DisplayContext.*  # Display management
│   ├── LvglStyle.*       # LVGL UI styling
│   ├── Tool.*            # Utility functions
│   ├── frame.*           # Boot animation frames
│   └── ...
├── library.properties    # Arduino library metadata
└── keywords.txt          # Syntax highlighting keywords
```

## 🚀 Getting Started

### Prerequisites

1. **Arduino IDE 2.x** or later
2. **ESP32 Board Package** installed
3. All libraries from `1_Libraries/` installed

### Arduino IDE Configuration

Configure the following settings in Arduino IDE:

| Setting | Value |
|---------|-------|
| Board | XIAO ESP32S3 |
| Partition Scheme | Maximum APP (7.9MB APP No OTA/No FS) |
| PSRAM | OPI PSRAM |
| USB Mode | USB-OTG (TinyUSB) |

### Uploading Firmware

1. Open `examples/main/main.ino` in Arduino IDE
2. Select the correct board and port
3. Click Upload

## 🏗️ Architecture

The firmware uses a **State Machine** architecture for managing different operational modes:

```
┌─────────────────┐
│   Main Menu     │◄────────────────┐
└────────┬────────┘                 │
         │                          │
    ┌────┴────┐                     │
    ▼         ▼                     │
┌───────┐ ┌───────┐                 │
│ UART  │ │ Power │──── Back ───────┤
│ Mode  │ │ Mode  │                 │
└───┬───┘ └───────┘                 │
    │                               │
    ▼                               │
┌───────┐                           │
│ Baud  │──── Back ─────────────────┘
│ Rate  │
└───────┘
```

## 📦 Core Components

### State Machine (`StateMachine.*`)
- Manages application states and transitions
- Handles state initialization and cleanup
- Provides error state fallback

### Input Task (`InputTask.*`)
- Handles rotary encoder rotation
- Debounces button presses
- Detects long press events
- Sends events to state machine via FreeRTOS queue

### Display Context (`DisplayContext.*`)
- Manages LVGL display operations
- Controls status LEDs
- Interfaces with INA228 power monitor

### DAPLink (`DapLink.*`)
- Implements CMSIS-DAP protocol
- Provides SWD debugging interface
- Handles USB HID communication

## 🔧 Key Functions

### Main Menu Functions

| Function | Description |
|----------|-------------|
| **UART Mode** | Serial bridge between USB and target device |
| **Power Mode** | Real-time voltage and current monitoring |

### UART Mode Features
- Configurable baud rate (9600 - 921600)
- TX/RX data visualization
- Auto-detect baud rate (future)

### Power Mode Features
- Real-time voltage display
- Current measurement
- Power calculation

## ⚙️ Configuration

### Hardware Pins (defined in `Global.h`)

```cpp
#define BOOT_BTN 0
#define ENCODER_PINA 18
#define ENCODER_PINB 17
#define UART_SWITCH 48
#define LED_DATA 9
#define LED_CLOCK 7
#define LED_LATCH 8
```

### Display Settings

```cpp
#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_90
```

## 🐛 Debugging

Serial debug output is available at the configured baud rate:

```cpp
ShowSerial.begin(FunctionBaudState::m_baudRate);
```

Debug messages can be viewed via the Arduino Serial Monitor.

## 📝 Adding New States

To add a new function state:

1. Create new state files (e.g., `NewFunctionState.h/.cpp`)
2. Inherit from `State` base class
3. Implement required virtual methods:
   - `enter()` - Called when entering state
   - `exit()` - Called when leaving state
   - `handleEvent()` - Process user input events
4. Register state in `main.ino`:
   ```cpp
   NewFunctionState* newState = new NewFunctionState();
   stateManager->registerState(newState);
   ```
5. Add menu item in main menu

## 📄 License

Part of the XIAO Debug Mate open-source hardware project by Seeed Studio.
