# ⚡ Hardware Documentation

This directory contains the hardware design documentation for the XIAO Debug Mate.

## 📁 Files Included

| File | Description |
|------|-------------|
| `Seeed_Studio_XIAO_Debug_Mate_V1.0_SCH_20250926.pdf` | Complete schematic diagram |

## 📋 Hardware Specifications

### Main Controller

| Parameter | Value |
|-----------|-------|
| Module | Seeed Studio XIAO ESP32-S3 |
| MCU | ESP32-S3 (Xtensa LX7 dual-core) |
| Clock Speed | 240 MHz |
| Flash | 8 MB |
| PSRAM | 8 MB (OPI) |
| USB | Native USB OTG |

### Display

| Parameter | Value |
|-----------|-------|
| Type | TFT LCD |
| Controller | ST7789 |
| Resolution | 240 × 320 pixels |
| Size | 2.0 inches |
| Interface | SPI |
| Color Depth | 16-bit (RGB565) |

### Power Monitor

| Parameter | Value |
|-----------|-------|
| IC | Texas Instruments INA228 |
| Interface | I2C (Address: 0x43) |
| Voltage Range | 0-85V |
| Current Sense | External shunt |
| Shunt Resistor | 68mΩ |
| Max Current | 1A |
| Resolution | 20-bit ADC |

### Storage

| Parameter | Value |
|-----------|-------|
| Type | I2C EEPROM |
| Interface | I2C (Address: 0x50) |
| Capacity | Varies by model |
| Purpose | Configuration storage |

### User Interface

| Component | Description |
|-----------|-------------|
| Rotary Encoder | Navigation input with push button |
| Status LEDs | Shift register controlled RGB LEDs |
| Boot Button | GPIO0 for mode selection |

## 🔌 Pinout Reference

### XIAO ESP32-S3 Pin Assignments

```
                    ┌─────────────┐
                    │  XIAO       │
                    │  ESP32-S3   │
         ┌──────────┤             ├──────────┐
         │          │             │          │
    D0 ──┤ GPIO1    │             │ GPIO44 ├── TX
    D1 ──┤ GPIO2    │             │ GPIO43 ├── RX
    D2 ──┤ GPIO3    │             │ GPIO7  ├── LED_CLK
    D3 ──┤ GPIO4    │             │ GPIO8  ├── LED_LATCH
    D4 ──┤ GPIO5    │             │ GPIO9  ├── LED_DATA
    D5 ──┤ GPIO6    │             │ GPIO17 ├── ENC_B
         │          │             │ GPIO18 ├── ENC_A
         │          │             │ GPIO48 ├── UART_SW
         │          │             │ GPIO0  ├── BOOT_BTN
         │          │             │ GPIO15 ├── MOS2
         │          │             │ GPIO16 ├── MOS1
         └──────────┤             ├──────────┘
                    │   USB-C     │
                    └─────────────┘
```

### I2C Bus Connections

| Device | SDA Pin | SCL Pin | Address | Speed |
|--------|---------|---------|---------|-------|
| INA228 | GPIO4 | GPIO3 | 0x43 | 100kHz |
| EEPROM | GPIO1 | GPIO2 | 0x50 | 100kHz |

### LED Shift Register

| Pin | Function |
|-----|----------|
| GPIO9 | Serial Data |
| GPIO7 | Clock |
| GPIO8 | Latch |

### Rotary Encoder

| Pin | Function |
|-----|----------|
| GPIO18 | Channel A |
| GPIO17 | Channel B |
| GPIO0 | Push Button (shared with BOOT) |

### UART Bridge

| Pin | Function |
|-----|----------|
| Serial0 RX | Target TX |
| Serial0 TX | Target RX |
| GPIO48 | UART Switch Control |

## 📊 Block Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                      XIAO Debug Mate                            │
│                                                                 │
│  ┌─────────────┐     ┌─────────────┐     ┌─────────────┐       │
│  │   XIAO      │     │   ST7789    │     │   INA228    │       │
│  │  ESP32-S3   │────▶│   Display   │     │  Power Mon  │       │
│  │             │     │  240×320    │     │             │       │
│  │   USB-OTG   │     └─────────────┘     └──────┬──────┘       │
│  └──────┬──────┘                                │              │
│         │         ┌─────────────┐               │              │
│         │         │   I2C       │◀──────────────┘              │
│         │         │   EEPROM    │                              │
│         │         └─────────────┘                              │
│         │                                                       │
│         │         ┌─────────────┐     ┌─────────────┐          │
│         │         │   Shift     │     │   Rotary    │          │
│         └────────▶│   Register  │     │   Encoder   │          │
│                   │   (LEDs)    │     │             │          │
│                   └─────────────┘     └─────────────┘          │
│                                                                 │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                   Debug Connector                        │   │
│  │   SWDIO  SWCLK  GND  3V3  RST  TX  RX                   │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

## ⚡ Power Architecture

```
USB 5V ──┬──▶ XIAO 3.3V LDO ──▶ Internal Logic
         │
         └──▶ Power Output ──▶ Target Device (optional)
                    │
                    └──▶ INA228 Current Sense ──▶ Measurement
```

### Power Specifications

| Parameter | Min | Typical | Max | Unit |
|-----------|-----|---------|-----|------|
| Input Voltage (USB) | 4.5 | 5.0 | 5.5 | V |
| Operating Current | - | 100 | 250 | mA |
| Target Power Output | - | 3.3 | - | V |
| Target Current Limit | - | - | 500 | mA |

## 🔧 Debug Interface

### SWD Connector Pinout

| Pin | Signal | Description |
|-----|--------|-------------|
| 1 | VCC | Target power (3.3V) |
| 2 | SWDIO | Serial Wire Data |
| 3 | SWCLK | Serial Wire Clock |
| 4 | GND | Ground |
| 5 | RST | Target Reset |

### UART Header Pinout

| Pin | Signal | Description |
|-----|--------|-------------|
| 1 | TX | Transmit (to target RX) |
| 2 | RX | Receive (from target TX) |
| 3 | GND | Ground |

## 📐 Mechanical Dimensions

| Parameter | Value |
|-----------|-------|
| PCB Length | ~90 mm |
| PCB Width | ~50 mm |
| Overall Height | ~25 mm (with housing) |

## 🛠️ Design Files

The schematic PDF provides:
- Complete circuit topology
- Component values and part numbers
- Net names for debugging
- Power distribution network

### Reading the Schematic

1. **Power Section** - USB input, regulators, power distribution
2. **MCU Section** - XIAO ESP32-S3 connections
3. **Display Section** - TFT interface and backlight
4. **Sensor Section** - INA228 and EEPROM
5. **Interface Section** - Debug connector and UART
6. **LED Section** - Shift register and status LEDs

## ⚠️ Design Considerations

### EMI/EMC
- Keep SWD traces short and matched
- Use ground plane under high-speed signals
- Add ferrite beads on power inputs

### Signal Integrity
- Maintain controlled impedance for SPI signals
- Use series termination resistors where needed
- Minimize crosstalk between analog and digital

### Thermal
- Ensure adequate copper pour for heat dissipation
- Consider airflow in enclosure design
- Monitor operating temperature during extended use

## 📚 References

- [ESP32-S3 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_en.pdf)
- [INA228 Datasheet](https://www.ti.com/lit/ds/symlink/ina228.pdf)
- [ST7789 Datasheet](https://www.crystalfontz.com/controllers/Sitronix/ST7789V/)
- [CMSIS-DAP Specification](https://arm-software.github.io/CMSIS_5/DAP/html/index.html)

