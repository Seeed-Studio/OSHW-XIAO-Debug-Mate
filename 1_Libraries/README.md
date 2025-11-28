# 📚 Required Libraries

This directory contains all the Arduino libraries required for the XIAO Debug Mate firmware.

## 📦 Installation

Copy all contents of this directory to your Arduino libraries folder:

```bash
# macOS
cp -r * ~/Documents/Arduino/libraries/

# Windows
xcopy /E /I * "%USERPROFILE%\Documents\Arduino\libraries\"

# Linux
cp -r * ~/Arduino/libraries/
```

## 📋 Library Overview

| Library | Version | Description | License |
|---------|---------|-------------|---------|
| **Adafruit_BusIO** | - | I2C and SPI abstraction layer | MIT |
| **Adafruit_INA228_Library** | 2.0.1+ | High-precision power monitor driver | MIT |
| **Adafruit_NeoPixel** | - | WS2812 RGB LED driver | LGPL |
| **Adafruit_SPIFlash** | - | SPI Flash memory support | MIT |
| **Adafruit_TinyUSB_Library** | 3.4.4+ | USB device stack for Arduino | MIT |
| **I2C_EEPROM** | 1.9.4 | I2C EEPROM read/write library | MIT |
| **lvgl_debug_mate** | 9.x | Light and Versatile Graphics Library | MIT |
| **MIDI_Library** | - | MIDI communication support | MIT |
| **SdFat_-_Adafruit_Fork** | - | SD card FAT filesystem | MIT |
| **Seeed_Arduino_DAPLink** | - | CMSIS-DAP debugger implementation | Apache 2.0 |
| **TFT_eSPI_Debug_Mate** | - | TFT display driver (ST7789) | BSD |

## 🔍 Library Details

### 🖥️ TFT_eSPI_Debug_Mate

Custom fork of TFT_eSPI optimized for the XIAO Debug Mate display.

**Features:**
- ST7789 driver support
- Hardware SPI acceleration
- LVGL integration ready
- Rotation support

**Configuration:** Pre-configured in `User_Setup.h` for Debug Mate hardware.

### 🎨 lvgl_debug_mate

LVGL (Light and Versatile Graphics Library) customized for Debug Mate.

**Features:**
- Animated boot screen
- Menu system widgets
- Power monitoring display
- Custom fonts and styles

**Configuration:** Settings in `lv_conf.h`

### 🐞 Seeed_Arduino_DAPLink

Implementation of ARM CMSIS-DAP protocol for debugging target devices.

**Supported Protocols:**
- SWD (Serial Wire Debug)
- JTAG (partial)

**Supported Targets:**
- ARM Cortex-M0/M0+
- ARM Cortex-M3/M4
- ARM Cortex-M33

### ⚡ Adafruit_INA228_Library

Driver for the INA228 high-precision power monitor IC.

**Capabilities:**
- Voltage measurement: 0-85V
- Current measurement (with external shunt)
- Power calculation
- Energy accumulation

**Debug Mate Config:**
```cpp
ina228.setShunt(0.068, 1.0);  // 68mΩ shunt, 1A max
ina228.setAveragingCount(INA228_COUNT_16);
```

### 🔌 Adafruit_TinyUSB_Library

USB device stack enabling USB functionality.

**Features Used:**
- USB CDC (Serial)
- USB HID (for DAPLink)
- Composite USB device

### 💾 I2C_EEPROM

Library for reading/writing I2C EEPROM chips.

**Usage:**
- Store user settings
- Persist baud rate configuration
- Save calibration data

### 🌈 Adafruit_NeoPixel

Control WS2812-compatible RGB LEDs.

**Usage:**
- Status indication
- Mode visualization
- Debug feedback

## ⚙️ Configuration Files

### `lv_conf.h`

Main LVGL configuration file. Key settings:

```c
#define LV_COLOR_DEPTH 16
#define LV_MEM_SIZE (48 * 1024)
#define LV_USE_ANIMIMG 1
#define LV_FONT_MONTSERRAT_14 1
```

## 🔗 Original Library Sources

If you need to update or modify these libraries, here are the original sources:

| Library | Repository |
|---------|------------|
| Adafruit_BusIO | https://github.com/adafruit/Adafruit_BusIO |
| Adafruit_INA228 | https://github.com/adafruit/Adafruit_INA228 |
| Adafruit_NeoPixel | https://github.com/adafruit/Adafruit_NeoPixel |
| Adafruit_SPIFlash | https://github.com/adafruit/Adafruit_SPIFlash |
| Adafruit_TinyUSB | https://github.com/adafruit/Adafruit_TinyUSB_Arduino |
| I2C_EEPROM | https://github.com/RobTillaart/I2C_EEPROM |
| LVGL | https://github.com/lvgl/lvgl |
| MIDI Library | https://github.com/FortySevenEffects/arduino_midi_library |
| SdFat | https://github.com/adafruit/SdFat |
| Seeed DAPLink | https://github.com/Seeed-Studio/Seeed_Arduino_DAPLink |
| TFT_eSPI | https://github.com/Bodmer/TFT_eSPI |

## ⚠️ Important Notes

1. **Use these specific versions** - The libraries in this folder are tested and configured for XIAO Debug Mate
2. **Don't mix versions** - Using different library versions may cause compatibility issues
3. **Custom configurations** - Some libraries have been customized for this hardware

## 🛠️ Troubleshooting

### Library Not Found Error
Make sure all libraries are copied to the correct Arduino libraries folder.

### Compilation Errors
1. Remove any duplicate libraries from your Arduino libraries folder
2. Restart Arduino IDE after installing libraries

### Display Not Working
Check that `TFT_eSPI_Debug_Mate` is being used, not the standard `TFT_eSPI` library.

