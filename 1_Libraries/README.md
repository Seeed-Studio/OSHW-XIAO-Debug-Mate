# 📚 Required Libraries

This directory contains all the Arduino libraries required for the XIAO Debug Mate firmware.

## 📦 Installation

### Option 1: Use Pre-packaged Libraries (Recommended)

Copy all contents of this directory to your Arduino libraries folder:

```bash
# macOS
cp -r * ~/Documents/Arduino/libraries/

# Windows
xcopy /E /I * "%USERPROFILE%\Documents\Arduino\libraries\"

# Linux
cp -r * ~/Arduino/libraries/
```

### Option 2: Install from Source

#### Step 1: Install from Arduino Library Manager

Open Arduino IDE → **Sketch → Include Library → Manage Libraries**, then install:

| Library | Recommended Version |
|---------|---------------------|
| **Adafruit INA228 Library** | 2.0.1 |
| **Adafruit TinyUSB Library** | 3.4.4 |

#### Step 2: Clone Custom Libraries

These libraries require specific branches. Open terminal and run:

```bash
# Go to the library directory
cd ~/Documents/Arduino/libraries

# DAPLink (custom ESP32-S3 branch)
git clone --depth 1 https://github.com/Lesords/Seeed_Arduino_DAPLink.git -b feat/ESP32S3

# TFT (custom ST7789-EVT branch)
git clone --depth 1 https://github.com/Lesords/TFT_eSPI.git -b feat/ST7789-EVT

# LVGL (custom Debugger branch)
git clone --depth 1 https://github.com/Lesords/lvgl.git -b feat/Debugger
```

## 📋 Library Overview

| Library | Version / Branch | Source | Description |
|---------|------------------|--------|-------------|
| **Seeed_Arduino_DAPLink** | `feat/ESP32S3` | [Lesords/Seeed_Arduino_DAPLink](https://github.com/Lesords/Seeed_Arduino_DAPLink/tree/feat/ESP32S3) | CMSIS-DAP debugger (ESP32-S3 fork) |
| **TFT_eSPI** | `feat/ST7789-EVT` | [Lesords/TFT_eSPI](https://github.com/Lesords/TFT_eSPI/tree/feat/ST7789-EVT) | TFT display driver (custom fork) |
| **lvgl** | `feat/Debugger` | [Lesords/lvgl](https://github.com/Lesords/lvgl/tree/feat/Debugger) | LVGL graphics library (custom fork) |
| **Adafruit_INA228** | 2.0.1 | [adafruit/Adafruit_INA228](https://github.com/adafruit/Adafruit_INA228) | Power monitor driver |
| **Adafruit_TinyUSB** | 3.4.4 | [adafruit/Adafruit_TinyUSB_Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) | USB device stack |
| **Adafruit_BusIO** | 1.17.4 | [adafruit/Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO) | I2C/SPI abstraction layer |
| **I2C_EEPROM** | 1.9.4 | [RobTillaart/I2C_EEPROM](https://github.com/RobTillaart/I2C_EEPROM) | I2C EEPROM library |
| **Adafruit_NeoPixel** | 1.3.3 | [adafruit/Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) | RGB LED driver |
| **Adafruit_SPIFlash** | 5.1.1 | [adafruit/Adafruit_SPIFlash](https://github.com/adafruit/Adafruit_SPIFlash) | SPI Flash support |
| **SdFat** | 2.3.54 | [adafruit/SdFat](https://github.com/adafruit/SdFat) | SD card FAT filesystem |
| **MIDI_Library** | 5.0.2 | [FortySevenEffects/arduino_midi_library](https://github.com/FortySevenEffects/arduino_midi_library) | MIDI communication |

## ⚠️ Important: Custom Library Branches

The following libraries **must** use specific custom branches to work with XIAO Debug Mate:

| Library | Required Branch | Why |
|---------|-----------------|-----|
| **Seeed_Arduino_DAPLink** | `feat/ESP32S3` | ESP32-S3 specific implementation |
| **TFT_eSPI** | `feat/ST7789-EVT` | Pre-configured for Debug Mate display |
| **lvgl** | `feat/Debugger` | Custom UI components and boot animation |

> ⚠️ Using the original/main branches will **not** work!

## 🔍 Library Details

### 🐞 Seeed_Arduino_DAPLink

Custom fork with ESP32-S3 support for CMSIS-DAP debugging.

**Branch:** `feat/ESP32S3`  
**Source:** https://github.com/Lesords/Seeed_Arduino_DAPLink

**Supported Protocols:**
- SWD (Serial Wire Debug)

**Supported Targets:**
- ARM Cortex-M0/M0+
- ARM Cortex-M3/M4
- ARM Cortex-M33

### 🖥️ TFT_eSPI

Custom fork optimized for the XIAO Debug Mate display.

**Branch:** `feat/ST7789-EVT`  
**Source:** https://github.com/Lesords/TFT_eSPI

**Features:**
- ST7789 driver support (240×296 resolution)
- Hardware SPI acceleration
- LVGL integration ready
- Pre-configured `User_Setup.h`

### 🎨 lvgl (LVGL Debug Mate)

LVGL (Light and Versatile Graphics Library) customized for Debug Mate.

**Branch:** `feat/Debugger`  
**Source:** https://github.com/Lesords/lvgl

**Features:**
- Animated boot screen
- Menu system widgets
- Power monitoring display
- Custom fonts and styles

**Configuration:** Settings in `lv_conf.h`

### ⚡ Adafruit_INA228

Driver for the INA228 high-precision power monitor IC.

**Version:** 2.0.1 (from Arduino Library Manager)  
**Source:** https://github.com/adafruit/Adafruit_INA228

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

### 🔌 Adafruit_TinyUSB

USB device stack enabling USB functionality.

**Version:** 3.4.4 (from Arduino Library Manager)  
**Source:** https://github.com/adafruit/Adafruit_TinyUSB_Arduino

**Features Used:**
- USB CDC (Serial)
- USB HID (for DAPLink)
- Composite USB device

### 💾 I2C_EEPROM

Library for reading/writing I2C EEPROM chips.

**Version:** 1.9.4  
**Source:** https://github.com/RobTillaart/I2C_EEPROM

**Usage:**
- Store user settings
- Persist baud rate configuration
- Save calibration data

## ⚙️ Configuration Files

### `lv_conf.h`

Main LVGL configuration file. Key settings:

```c
#define LV_COLOR_DEPTH 16
#define LV_MEM_SIZE (48 * 1024)
#define LV_USE_ANIMIMG 1
#define LV_FONT_MONTSERRAT_14 1
```

## 🛠️ Troubleshooting

### Library Not Found Error
Make sure all libraries are copied to the correct Arduino libraries folder.

### Compilation Errors
1. Ensure you're using the correct custom branches (not main/master)
2. Remove any duplicate libraries from your Arduino libraries folder
3. Restart Arduino IDE after installing libraries

### Display Not Working
Check that you're using `TFT_eSPI` from the `feat/ST7789-EVT` branch, not the standard library.

### DAPLink Not Working
Ensure you're using `Seeed_Arduino_DAPLink` from the `feat/ESP32S3` branch.
