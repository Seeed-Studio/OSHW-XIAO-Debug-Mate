# 🎯 DAPLink Package v1.0

This directory contains pre-compiled example binaries, target configurations, and OpenOCD tools for debugging various XIAO boards with the XIAO Debug Mate.

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
- **Flash:** 256KB
- **RAM:** 32KB

### XIAO RA4M1
- **File:** `target/XIAO_RA4M1/ra4m1.cfg`
- **MCU:** Renesas R7FA4M1AB
- **Core:** ARM Cortex-M4
- **Flash:** 256KB
- **RAM:** 32KB

## 🛠️ Using OpenOCD (for XIAO MG24)

The XIAO MG24 requires OpenOCD for debugging due to its Silicon Labs EFR32MG24 chip.

### macOS / Linux

```bash
# Navigate to OpenOCD directory
cd XIAO_MG24_Mac_Linux_OpenOCD-v0.12.0/bin

# Make executable (first time only)
chmod +x openocd

# Run OpenOCD with XIAO Debug Mate
./openocd -f interface/cmsis-dap.cfg -f target/efm32s2.cfg
```

### Windows

```cmd
# Navigate to OpenOCD directory
cd XIAO_MG24_Win_OpenOCD-v0.12.0\bin

# Run OpenOCD with XIAO Debug Mate
openocd.exe -f interface/cmsis-dap.cfg -f target/efm32s2.cfg
```

### Common OpenOCD Commands

Once OpenOCD is running, connect via telnet (port 4444):

```bash
# Connect to OpenOCD
telnet localhost 4444

# Common commands:
reset halt          # Reset and halt the target
flash write_image erase firmware.hex   # Flash firmware
reset run           # Reset and run
exit                # Exit OpenOCD
```

## 📡 Programming with DAPLink

### Using Arduino IDE

For boards supported by Arduino IDE (SAMD21, RA4M1, nRF52840, RP2040, RP2350):

1. Connect XIAO Debug Mate to target board
2. Select target board in Arduino IDE
3. Select "CMSIS-DAP" as programmer
4. Use "Upload Using Programmer" or regular upload

### Using pyOCD

```bash
# Install pyOCD
pip install pyocd

# List connected probes
pyocd list

# Flash firmware
pyocd flash -t <target> firmware.hex

# Start GDB server
pyocd gdbserver -t <target>
```

Supported target names:
- `atsamd21g18a` - XIAO SAMD21
- `nrf52840` - XIAO nRF52840
- `rp2040` - XIAO RP2040

### Using OpenOCD

```bash
# Generic SWD interface
openocd -f interface/cmsis-dap.cfg -f target/<target>.cfg

# Flash example
openocd -f interface/cmsis-dap.cfg -f target/at91samd21g18.cfg \
  -c "program Blink_SAMD21.bin verify reset exit 0x00000000"
```

## 🔌 Connection Guide

### SWD Connection

| Debug Mate | Target | Description |
|------------|--------|-------------|
| SWDIO | SWDIO | Serial Wire Data |
| SWCLK | SWCLK | Serial Wire Clock |
| GND | GND | Ground |
| 3V3 | VCC | Power (optional) |
| RST | RST | Reset (optional) |

### Typical Setup

```
┌─────────────────┐      ┌─────────────────┐
│  XIAO Debug     │      │   Target XIAO   │
│     Mate        │      │     Board       │
│                 │      │                 │
│    SWDIO ●──────┼──────┼─● SWDIO        │
│    SWCLK ●──────┼──────┼─● SWCLK        │
│      GND ●──────┼──────┼─● GND          │
│      3V3 ●──────┼──────┼─● 3V3          │
│      RST ●──────┼──────┼─● RST          │
└─────────────────┘      └─────────────────┘
```

## ⚠️ Troubleshooting

### Target Not Detected

1. Check SWD connections (SWDIO, SWCLK, GND)
2. Verify target is powered
3. Try reducing SWD clock speed
4. Check for shorts on the debug connector

### Flash Programming Failed

1. Ensure correct target configuration
2. Verify firmware file format (.bin, .hex, .elf)
3. Check flash address alignment
4. Confirm sufficient power supply

### OpenOCD Connection Issues

1. Verify CMSIS-DAP interface is detected
2. Check USB connection to Debug Mate
3. Update OpenOCD to latest version
4. Try different USB port

## 📚 Additional Resources

- [ARM CMSIS-DAP Documentation](https://arm-software.github.io/CMSIS_5/DAP/html/index.html)
- [OpenOCD User Manual](https://openocd.org/doc/html/index.html)
- [pyOCD Documentation](https://pyocd.io/)

