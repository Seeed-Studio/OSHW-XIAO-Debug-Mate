# 🔧 XIAO Debug Mate Firmware

This directory contains the main firmware source code for the XIAO Debug Mate. The firmware is structured as an **Arduino Library** and must be installed in your Arduino libraries folder to use.

## 📦 Installation

### Method 1: Copy to Arduino Libraries (Recommended)

Copy the entire `0_Firmware` folder to your Arduino libraries directory and rename it:

```bash
# macOS
cp -r 0_Firmware ~/Documents/Arduino/libraries/Seeed_Debugger

# Windows
xcopy /E /I 0_Firmware "%USERPROFILE%\Documents\Arduino\libraries\Seeed_Debugger"

# Linux
cp -r 0_Firmware ~/Arduino/libraries/Seeed_Debugger
```

### Method 2: Symbolic Link (For Development)

Create a symbolic link if you want to develop and modify the firmware:

```bash
# macOS / Linux
ln -s "$(pwd)/0_Firmware" ~/Documents/Arduino/libraries/Seeed_Debugger

# Windows (Run as Administrator)
mklink /D "%USERPROFILE%\Documents\Arduino\libraries\Seeed_Debugger" "%cd%\0_Firmware"
```

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
│   ├── InputTask.*       # Scroll wheel and button input handling
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
2. **ESP32 Board Package** version 3.1.3 installed via Board Manager
3. All libraries from `1_Libraries/` installed (see [1_Libraries/README.md](../1_Libraries/README.md))
4. This firmware library installed (see Installation above)

### Step 1: Install Required Libraries

Copy all libraries from `1_Libraries/` to your Arduino libraries folder:

```bash
# macOS
cp -r ../1_Libraries/* ~/Documents/Arduino/libraries/

# Windows
xcopy /E /I ..\1_Libraries\* "%USERPROFILE%\Documents\Arduino\libraries\"

# Linux
cp -r ../1_Libraries/* ~/Arduino/libraries/
```

### Step 2: Modify ESP32 Core Files

> ⚠️ **Important:** You must modify the ESP32 Arduino core files to disable default USB initialization, otherwise TinyUSB will conflict with the default USB stack.

**Locate the ESP32 core files:**

| OS | Path |
|----|------|
| 🍎 **macOS** | `~/Library/Arduino15/packages/esp32/hardware/esp32/3.1.3/cores/esp32/` |
| 🪟 **Windows** | `%LOCALAPPDATA%\Arduino15\packages\esp32\hardware\esp32\3.1.3\cores\esp32\` |
| 🐧 **Linux** | `~/.arduino15/packages/esp32/hardware/esp32/3.1.3/cores/esp32/` |

**Modify the following 3 files:**

#### File 1: `USB.cpp` (around line 352)
```cpp
// Before:
ESPUSB USB;

// After:
// ESPUSB USB;
```

#### File 2: `USB.h` (around line 119)
```cpp
// Before:
extern ESPUSB USB;

// After:
// extern ESPUSB USB;
```

#### File 3: `main.cpp` (around lines 98 and 101)
```cpp
// Before:
#if ARDUINO_USB_DFU_ON_BOOT && !ARDUINO_USB_MODE
    USB.enableDFU();
#endif
#if ARDUINO_USB_ON_BOOT && !ARDUINO_USB_MODE
    USB.begin();
#endif

// After:
#if ARDUINO_USB_DFU_ON_BOOT && !ARDUINO_USB_MODE
    // USB.enableDFU();
#endif
#if ARDUINO_USB_ON_BOOT && !ARDUINO_USB_MODE
    // USB.begin();
#endif
```

### Step 3: Configure Arduino IDE

Configure the following settings in Arduino IDE:

| Setting | Value |
|---------|-------|
| **Board** | XIAO ESP32S3 |
| **Partition Scheme** | Maximum APP (7.9MB APP No OTA/No FS) |
| **PSRAM** | OPI PSRAM |
| **USB Mode** | USB-OTG (TinyUSB) |

### Step 4: Open and Upload

1. In Arduino IDE, go to **File → Examples → Seeed All-in-one Debugger → main**
2. Or open `examples/main/main.ino` directly
3. Select the correct port (your XIAO Debug Mate)
4. Click **Upload**

> 💡 **Tip:** If the device is not detected, enter Boot Mode by holding BOOT button while pressing RESET.

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
- Handles scroll wheel rotation
- Debounces button presses
- Detects long press events
- Sends events to state machine via FreeRTOS queue

### Display Context (`DisplayContext.*`)
- Manages LVGL display operations
- Controls 36-LED status matrix
- Interfaces with INA228 power monitor

### DAPLink (`DapLink.*`)
- Implements CMSIS-DAP protocol
- Provides SWD debugging interface
- Handles USB HID communication

## 🔧 Key Functions

### Main Menu Functions

| Function | Description |
|----------|-------------|
| **UART Mode** | Serial monitor & UART passthrough |
| **Power Mode** | Precision power profiling (μA level) |

### UART Mode Features
- Configurable baud rate (9600 - 921600)
- Real-time TX/RX data visualization on display
- 36-LED matrix shows current baud rate

### Power Mode Features
- Real-time voltage/current display
- μA level precision (factory-calibrated)
- Peak/valley identification

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
#define TFT_VER_RES   296
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

1. Create new state files (e.g., `NewFunctionState.h/.cpp`) in the `src/` folder
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
5. Add menu item in MainMenuState

## ⚠️ Troubleshooting

### Library Not Found

If Arduino IDE can't find the library:
1. Make sure the folder is named correctly in the libraries directory
2. Restart Arduino IDE after installing
3. Check **File → Examples** to see if "Seeed All-in-one Debugger" appears

### Compilation Errors

1. Ensure all dependencies from `1_Libraries/` are installed
2. Check that ESP32 board package version is 3.1.3
3. Verify Arduino IDE settings match the table above
4. **If you see USB-related errors:** Make sure you've modified the ESP32 core files (see Step 2)

### USB Conflict / TinyUSB Not Working

If DAPLink or USB functionality doesn't work:
1. Verify you've commented out the USB initialization in the ESP32 core files
2. Make sure you modified all 3 files: `USB.cpp`, `USB.h`, and `main.cpp`
3. Restart Arduino IDE after modifying core files

### Upload Failed

1. Enter Boot Mode: Hold BOOT → Press RESET → Release BOOT
2. Select the correct COM port
3. Try a different USB cable (use data cable, not charge-only)

## 📄 License

Part of the XIAO Debug Mate open-source hardware project by Seeed Studio.
