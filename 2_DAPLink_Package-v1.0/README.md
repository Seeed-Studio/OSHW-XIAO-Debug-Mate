# 🎯 DAPLink Package v1.0

This directory contains pre-compiled example binaries, target configurations, and OpenOCD tools for debugging various XIAO boards with the XIAO Debug Mate.

## 📖 Documentation

For complete usage instructions, please refer to the official Wiki:

👉 **[DAPLink Debugger Wiki](https://wiki.seeedstudio.com/xiao_debug_mate_debug/)**

The Wiki provides comprehensive guides on:
- Understanding debugger concepts (GDB, OpenOCD, PyOCD, CMSIS-DAP)
- Step-by-step debugging tutorials
- Flashing firmware using OpenOCD/PyOCD
- Using debugging with PlatformIO
- Troubleshooting common issues

## 📁 Directory Structure

```
2_DAPLink_Package-v1.0/
├── examples/                    # Pre-compiled test binaries
│   ├── Blink_*.bin/hex         # Blink examples for each target
│   └── Bootloader_*.bin/hex    # Bootloader files
├── target/                      # OpenOCD target configurations
│   ├── XIAO_RA4M1/             # Renesas RA4M1 config
│   └── XIAO_SAMD21/            # Microchip SAMD21 config
├── XIAO_MG24_Mac_Linux_OpenOCD-v0.12.0/  # OpenOCD for Mac/Linux
└── XIAO_MG24_Win_OpenOCD-v0.12.0/        # OpenOCD for Windows
```

## 🎯 Compatibility

| XIAO Model | DAPLink Debug | UART Monitor | Power Analyzer |
|------------|---------------|--------------|----------------|
| XIAO SAMD21 | ✅ | ✅ | ✅ |
| XIAO RA4M1 | ✅ | ✅ | ✅ |
| XIAO nRF52840 (Sense) | ✅ | ✅ | ✅ |
| XIAO RP2040 | ✅ | ✅ | ✅ |
| XIAO RP2350 | ✅ | ✅ | ✅ |
| XIAO MG24 (Sense) | ✅ | ✅ | ✅ |
| XIAO nRF54L15 | ❌ | ✅ | ✅ |
| XIAO ESP32C3/S3/C6 | ❌ | ✅ | ✅ |

> ⚠️ **Note:** DAPLink debugging only works with ARM Cortex-M cores. XIAO nRF54L15 and ESP32 series do not support DAPLink debugging.

## 🔧 Pre-compiled Examples

Test binaries to verify your debugging setup:

| File | Target Board | Description |
|------|--------------|-------------|
| `Blink_SAMD21.bin/.hex` | XIAO SAMD21 | LED blink test |
| `Blink_RA4M1.bin/.hex` | XIAO RA4M1 | LED blink test |
| `Blink_nRF52840.bin/.hex/.elf` | XIAO nRF52840 | LED blink test |
| `Blink_RP2040.bin/.elf` | XIAO RP2040 | LED blink test |
| `Blink_RP2350.bin/.elf` | XIAO RP2350 | LED blink test |
| `Blink_MG24.hex` | XIAO MG24 | LED blink test |
| `Bootloader_SAMD21.bin` | XIAO SAMD21 | UF2 bootloader |
| `Bootloader_RA4M1.hex` | XIAO RA4M1 | Bootloader |
| `Bootloader_nRF52840-0.6.1.hex` | XIAO nRF52840 | Adafruit bootloader |

## 🎯 Target Configurations

### XIAO SAMD21
- **File:** `target/XIAO_SAMD21/at91samd21g18.cfg`
- **MCU:** Microchip ATSAMD21G18A
- **Core:** ARM Cortex-M0+

### XIAO RA4M1
- **File:** `target/XIAO_RA4M1/ra4m1.cfg`
- **MCU:** Renesas R7FA4M1AB
- **Core:** ARM Cortex-M4

## 🚀 Quick Start

### Install Required Tools

```bash
# Install OpenOCD (recommended: xpack-openocd 0.12.0)
# Or use the bundled OpenOCD in XIAO_MG24_*/

# Install PyOCD (alternative)
pip install pyocd
```

### Flash Firmware Example

```bash
# Using OpenOCD
openocd -f interface/cmsis-dap.cfg -f target/at91samd21g18.cfg \
  -c "program examples/Blink_SAMD21.hex verify reset exit"

# Using PyOCD
pyocd flash -t atsamd21g18a examples/Blink_SAMD21.hex
```

## 📚 Resources

- 📖 [DAPLink Debugger Wiki](https://wiki.seeedstudio.com/xiao_debug_mate_debug/)
- 📖 [UART Monitor Wiki](https://wiki.seeedstudio.com/xiao_debug_mate_uart/)
- 📖 [Power Meter Wiki](https://wiki.seeedstudio.com/xiao_debug_mate_power/)
- 🔗 [ARM CMSIS-DAP Documentation](https://arm-software.github.io/CMSIS_5/DAP/html/index.html)
- 🔗 [OpenOCD User Manual](https://openocd.org/doc/html/index.html)
- 🔗 [PyOCD Documentation](https://pyocd.io/)
