<p align="center">
  <h1 align="center">🔧 XIAO Debug Mate</h1>
  <p align="center">
    <strong>An Open-Source ESP32-S3 Multi-Tool for Embedded System Debugging</strong>
  </p>
  <p align="center">
    🐞 DAPLink Debugger | 📡 UART Monitor | ⚡ Power Profiler | 🖥️ Visual Feedback
  </p>
</p>

<p align="center">
  <a href="#-features">Features</a> •
  <a href="#-hardware">Hardware</a> •
  <a href="#-getting-started">Getting Started</a> •
  <a href="#-project-structure">Project Structure</a> •
  <a href="#-license">License</a>
</p>

<p align="center">
  <a href="https://www.seeedstudio.com/Seeed-Studio-XIAO-Debug-Mate-p-6588.html">
    <img src="https://img.shields.io/badge/🛒_Buy_Now-Seeed_Studio-green?style=for-the-badge" alt="Buy Now">
  </a>
  <a href="https://wiki.seeedstudio.com/getting_started_with_xiao_debug_mate/">
    <img src="https://img.shields.io/badge/📖_Wiki-Documentation-blue?style=for-the-badge" alt="Wiki">
  </a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Latest_Firmware-v1.1-brightgreen?style=for-the-badge" alt="Latest Firmware">
  <img src="https://img.shields.io/badge/Platform-ESP32--S3-blue?style=for-the-badge" alt="Platform">
  <img src="https://img.shields.io/badge/License-OSHW-orange?style=for-the-badge" alt="License">
</p>

---

## 📖 Introduction

**Seeed Studio XIAO Debug Mate** is an open-source ESP32-S3 multi-tool that simplifies embedded system debugging with visual feedback. This all-in-one device features a standalone 2.01 inch TFT LCD display, LED status matrix, and native Seeed Studio XIAO support, delivering essential debugging functions: DAPLink chip-level debugging, built-in serial monitoring with UART passthrough, and accurate power consumption measurement. Plug-and-play design eliminates complex wiring for streamlined development.

## ✨ Features

### 🛠️ 3-in-1 Professional Development Tool

| Feature | Description |
|---------|-------------|
| 🐞 **DAPLink-Compatible SWD Interface** | Powered by ESP32-S3 with full OpenOCD/PyOCD support, delivering professional-grade debugging capabilities. Set breakpoints, step through code, inspect memory, and access low-level hardware operations with precision. |
| 📡 **Intelligent Serial Monitor & UART Passthrough** | Monitor communications between your XIAO and the Debug Mate, or between the Debug Mate and external UART devices (Arduino, Raspberry Pi, Grove sensors). View real-time serial data on the onboard display or redirect to PC for detailed analysis. |
| ⚡ **Precision Power Profiling** | Track power consumption down to μA levels. Monitor voltage/current readings, ultra-low-power states, and consumption patterns with peak/valley identification. Factory-calibrated for maximum accuracy (±10% @ 1-10μA). |

### 🖥️ Standalone Visual Feedback System

Monitor key system metrics **without connecting to a PC**. The integrated 2.01" LCD screen displays real-time serial communications, power consumption readings, and UART data streams, while the programmable 36-LED matrix provides instant baud rate indicators. Perfect for on-site field testing, mobile development, and quick system power consumption checks.

### 🔌 Open-Source Platform with Universal Compatibility

Purpose-built for the **Seeed Studio XIAO ecosystem** with direct plug-and-play connection—any pre-soldered XIAO board connects instantly without tedious wiring. The thoughtfully designed pin headers and sockets transform the device into a specialized expansion breadboard for XIAO development. While optimized for XIAO, the open-source design extends compatibility to **any ARM Cortex-M microcontroller** via standard SWD and UART interfaces.

## 📋 Specifications

| Parameter | Description |
|-----------|-------------|
| **Processor** | Espressif ESP32-S3 |
| **Power Input** | USB-C 5V/1A |
| **Display** | 2.01 inch TFT LCD (240 × 296 resolution) |
| **LED** | 36-LED Matrix for Status Indication (Default: Baud Rate) |
| **User Input** | 1 × User Button/Boot Button, 1 × Scroll Wheel, 1 × Recessed Reset Button |
| **I/O Interface** | 14 × XIAO Standard Pins, 8 × Expansion Pins, 4 × SWD Debugging Pins, 1 × UART Grove Connector |
| **Product Size** | 100 × 56 × 20 mm |
| **Software** | Supports DAPLink for debugging |
| **Enclosure** | 3D-Printed in Black PLA |

## 🎯 Supported Target Boards

| Board | Interface | Status |
|-------|-----------|--------|
| 🟢 XIAO SAMD21 | SWD | ✅ Supported |
| 🟢 XIAO RA4M1 | SWD | ✅ Supported |
| 🟢 XIAO nRF52840 (Sense) | SWD | ✅ Supported |
| 🟢 XIAO RP2040 | SWD | ✅ Supported |
| 🟢 XIAO RP2350 | SWD | ✅ Supported |
| 🟢 XIAO MG24 (Sense) | SWD (OpenOCD) | ✅ Supported |

> ⚠️ **Note:** XIAO nRF54L15 and XIAO ESP32 series (C3/S3/C6) do **not** currently support debugging feature.

## 🚀 Getting Started

### ⚡ Quick Flash (Recommended for Users)

If you just want to use the XIAO Debug Mate, flash the pre-compiled firmware:

1. Install esptool: `pip install esptool`
2. Connect XIAO Debug Mate via USB-C
3. Enter download mode (hold BOOT, press RESET)
4. Run the flash script:

| OS | How to Run |
|----|------------|
| 🍎 **macOS** | Open Terminal, navigate to `5_Release_firmware/`, run `./flash.sh` |
| 🐧 **Linux** | Open Terminal, navigate to `5_Release_firmware/`, run `./flash.sh` |
| 🪟 **Windows** | Double-click `flash.bat` |

```bash
# macOS / Linux
cd 5_Release_firmware
./flash.sh
```

> The script automatically detects and flashes the latest firmware version!

---

### 🛠️ Build from Source (For Developers)

#### Prerequisites

- **Arduino IDE** 2.x or later
- **ESP32 Board Support** installed via Arduino Board Manager
- **USB-C Cable** for programming

#### Quick Start

1️⃣ **Clone the Repository**
```bash
git clone https://github.com/Seeed-Studio/OSHW-XIAO-Debug-Mate.git
cd OSHW-XIAO-Debug-Mate
```

2️⃣ **Install Libraries**

Copy all libraries from `1_Libraries/` to your Arduino libraries folder:
```bash
cp -r 1_Libraries/* ~/Documents/Arduino/libraries/
```

3️⃣ **Configure Arduino IDE**

Set the following options in Arduino IDE:
- **Board**: "XIAO ESP32S3"
- **Partition Scheme**: "Maximum APP (7.9MB APP No OTA/No FS)"
- **PSRAM**: "OPI PSRAM"
- **USB Mode**: "USB-OTG (TinyUSB)"

4️⃣ **Upload Firmware**

Open `0_Firmware/examples/main/main.ino` and upload to your XIAO Debug Mate.

## 📁 Project Structure

```
OSHW-XIAO-Debug-Mate/
├── 📂 0_Firmware/           # 🔧 Main firmware source code
│   ├── examples/            # Arduino sketch entry point
│   └── src/                 # Core library source files
│
├── 📂 1_Libraries/          # 📚 Required Arduino libraries
│   ├── Adafruit_BusIO/      # I2C/SPI communication
│   ├── Adafruit_INA228/     # Power monitoring sensor
│   ├── Adafruit_TinyUSB/    # USB device support
│   ├── lvgl_debug_mate/     # LVGL graphics library
│   ├── Seeed_Arduino_DAPLink/  # DAPLink implementation
│   ├── TFT_eSPI_Debug_Mate/ # TFT display driver
│   └── ...                  # Other supporting libraries
│
├── 📂 2_DAPLink_Package/    # 🎯 DAPLink tools and examples
│   ├── examples/            # Pre-compiled test binaries
│   ├── target/              # OpenOCD target configurations
│   └── XIAO_MG24_*/         # OpenOCD for MG24 debugging
│
├── 📂 3_Product_housing/    # 🏠 3D printable enclosure
│   └── *.stp, *.3mf         # CAD files for housing
│
├── 📂 4_Hardware/           # ⚡ Hardware documentation
│   └── *.pdf                # Schematic diagrams
│
└── 📂 5_Release_firmware/   # 📦 Pre-compiled firmware binaries
    ├── firmware-v*.bin      # Ready-to-flash firmware
    ├── flash.sh             # One-click flash (macOS/Linux)
    └── flash.bat            # One-click flash (Windows)
```

## 🖥️ User Interface

The XIAO Debug Mate features an intuitive menu system:

```
┌─────────────────────────────────┐
│         🏠 Main Menu            │
├─────────────────────────────────┤
│  📡  Function UART              │
│  ⚡  Function Power             │
└─────────────────────────────────┘
```

### Navigation
- **🔄 Scroll Wheel** - Navigate menu items
- **👆 Press** - Select/Confirm
- **👆 Long Press** - Back/Exit

## ⚙️ Configuration

### Baud Rate Options
The UART bridge supports multiple baud rates:
- 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600

### Power Monitoring
- **Accuracy**: ±10% @ 1-10μA (factory-calibrated)
- **Current Range**: μA to mA level precision
- **Features**: Peak/valley identification, real-time monitoring

## 🔗 Resources

- 🛒 [**Buy XIAO Debug Mate**](https://www.seeedstudio.com/Seeed-Studio-XIAO-Debug-Mate-p-6588.html)
- 📖 [**Wiki Documentation**](https://wiki.seeedstudio.com/getting_started_with_xiao_debug_mate/)
- 💻 [**GitHub Repository**](https://github.com/Seeed-Studio/OSHW-XIAO-Debug-Mate)

## 🤝 Contributing

We welcome contributions! Please feel free to:

- 🐛 Report bugs
- 💡 Suggest new features
- 🔧 Submit pull requests
- 📖 Improve documentation

## 📄 License

This project is open-source hardware (OSHW). See individual library directories for their specific licenses.

## 🙏 Acknowledgments

- **Seeed Studio** - Hardware design and development
- **LVGL** - Graphics library
- **Adafruit** - Various Arduino libraries
- **ARM** - CMSIS-DAP protocol
- **[啊猫啊狗晒太阳](https://space.bilibili.com/1155738723)** - [Design inspiration](https://www.bilibili.com/video/BV1Sc411273Y/) for the LED matrix

---

<p align="center">
  Made with ❤️ by <a href="https://www.seeedstudio.com">Seeed Studio</a>
</p>

<p align="center">
  <sub>🌟 Star us on GitHub — it motivates us a lot!</sub>
</p>
