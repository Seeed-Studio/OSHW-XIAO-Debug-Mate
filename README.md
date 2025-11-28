<p align="center">
  <h1 align="center">🔧 XIAO Debug Mate</h1>
  <p align="center">
    <strong>An Open-Source All-in-One Debugging Tool for Makers</strong>
  </p>
  <p align="center">
    🚀 DAPLink Debugger | 📊 Power Monitor | 📡 UART Bridge | 🖥️ Beautiful TFT Display
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
  <img src="https://img.shields.io/badge/Latest_Firmware-v1.1-brightgreen?style=for-the-badge" alt="Latest Firmware">
  <img src="https://img.shields.io/badge/Platform-ESP32--S3-blue?style=for-the-badge" alt="Platform">
  <img src="https://img.shields.io/badge/License-OSHW-orange?style=for-the-badge" alt="License">
</p>

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🐞 **DAPLink Debugger** | Program and debug ARM Cortex-M microcontrollers via SWD/JTAG |
| ⚡ **Power Monitoring** | Real-time voltage and current measurement with INA228 |
| 📡 **UART Bridge** | Configurable baud rate serial communication |
| 🖥️ **TFT Display** | 240x320 color display with LVGL-based beautiful UI |
| 🎛️ **Rotary Encoder** | Intuitive navigation and control |
| 💾 **EEPROM Storage** | Persistent settings storage |
| 🌈 **RGB Status LEDs** | Visual feedback for different operating modes |

## 🛠️ Hardware

XIAO Debug Mate is built around the **Seeed Studio XIAO ESP32-S3** module, featuring:

- **MCU**: ESP32-S3 with dual-core 240MHz processor
- **Display**: 2.0" ST7789 TFT LCD (240×320)
- **Power Monitor**: INA228 high-precision power sensor
- **Storage**: I2C EEPROM for configuration persistence
- **Interface**: Rotary encoder with push button
- **Connectors**: Debug target connector, UART header

## 🎯 Supported Target Boards

XIAO Debug Mate supports debugging the following XIAO series boards:

| Board | Interface | Status |
|-------|-----------|--------|
| 🟢 XIAO SAMD21 | SWD | ✅ Supported |
| 🟢 XIAO RA4M1 | SWD | ✅ Supported |
| 🟢 XIAO nRF52840 | SWD | ✅ Supported |
| 🟢 XIAO RP2040 | SWD | ✅ Supported |
| 🟢 XIAO RP2350 | SWD | ✅ Supported |
| 🟢 XIAO MG24 | SWD (OpenOCD) | ✅ Supported |

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
│   ├── Adafruit_NeoPixel/   # RGB LED control
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
- **🔄 Rotate** - Navigate menu items
- **👆 Press** - Select/Confirm
- **👆 Long Press** - Back/Exit

## ⚙️ Configuration

### Baud Rate Options
The UART bridge supports multiple baud rates:
- 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600

### Power Monitoring
- **Voltage Range**: 0-36V
- **Current Range**: 0-1A
- **Shunt Resistor**: 68mΩ

## 🔌 Pin Mapping

| Function | GPIO Pin |
|----------|----------|
| Encoder A | GPIO18 |
| Encoder B | GPIO17 |
| Boot Button | GPIO0 |
| UART Switch | GPIO48 |
| LED Data | GPIO9 |
| LED Clock | GPIO7 |
| LED Latch | GPIO8 |
| INA228 SDA | GPIO4 |
| INA228 SCL | GPIO3 |
| EEPROM SDA | GPIO1 |
| EEPROM SCL | GPIO2 |

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

---

<p align="center">
  Made with ❤️ by <a href="https://www.seeedstudio.com">Seeed Studio</a>
</p>

<p align="center">
  <sub>🌟 Star us on GitHub — it motivates us a lot!</sub>
</p>

