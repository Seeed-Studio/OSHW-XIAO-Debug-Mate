# 📦 Release Firmware

This directory contains pre-compiled firmware binaries for the XIAO Debug Mate.

## 📋 Available Versions

| Version | File | Size | Release Date | Status |
|---------|------|------|--------------|--------|
| **v1.1** | `firmware-v1.1.bin` | 5.2 MB | 2025 | ✅ **Latest** |
| v1.0 | `firmware-v1.0.bin` | 8.0 MB | 2025 | Factory Version |

## 🚀 Quick Flash

### One-Click Flash (Recommended)

Run the flash script for your operating system:

| OS | Script | How to Run |
|----|--------|------------|
| 🍎 **macOS** | `flash.sh` | Open Terminal → `cd` to this folder → run `./flash.sh` |
| 🐧 **Linux** | `flash.sh` | Open Terminal → `cd` to this folder → run `./flash.sh` |
| 🪟 **Windows** | `flash.bat` | Double-click the file |

**macOS / Linux:**
```bash
cd /path/to/5_Release_firmware
./flash.sh
```

**Windows:**
Simply double-click `flash.bat`

> **Note:** The scripts automatically detect and flash the newest firmware version in the folder.

### Prerequisites

1. **Install esptool**
   ```bash
   pip install esptool
   ```

2. **Connect XIAO Debug Mate via USB-C**

3. **Enter Download Mode** (if needed)
   - Hold the BOOT button
   - Press and release the RESET button
   - Release the BOOT button

### Manual Flash

If you prefer to flash manually or need a specific version:

```bash
# macOS (replace /dev/cu.usbmodemXXXX with your actual port)
esptool.py --chip esp32s3 --port /dev/cu.usbmodem1301 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z \
  --flash_mode keep --flash_freq keep --flash_size keep \
  0x10000 firmware-v1.1.bin

# Linux
esptool.py --chip esp32s3 --port /dev/ttyACM0 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z \
  --flash_mode keep --flash_freq keep --flash_size keep \
  0x10000 firmware-v1.1.bin

# Windows (replace COM3 with your actual port)
esptool.exe --chip esp32s3 --port COM3 --baud 921600 ^
  --before default_reset --after hard_reset write_flash -z ^
  --flash_mode keep --flash_freq keep --flash_size keep ^
  0x10000 firmware-v1.1.bin
```

### Advanced Options

```bash
# Find your port
# macOS:
ls /dev/cu.usb*

# Linux:
ls /dev/ttyUSB* /dev/ttyACM*

# Erase flash before writing (use if having issues)
esptool.py --chip esp32s3 erase_flash

# Verify after writing
esptool.py --chip esp32s3 --port /dev/cu.usbmodem1301 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z --verify \
  --flash_mode keep --flash_freq keep --flash_size keep \
  0x10000 firmware-v1.1.bin
```

---

## 📝 Release Notes

### 🆕 Version 1.1 (Latest)

**Release Highlights:**
- 🎨 **Redesigned Display UI** - Improved visual layout and user experience
- 🐛 **Bug Fixes** - Resolved display ghosting issues

**Detailed Changes:**

| Category | Description |
|----------|-------------|
| 🖥️ Display | Completely redesigned display page layout |
| 🖥️ Display | Optimized screen refresh mechanism |
| 🐛 Bug Fix | Fixed display ghosting/artifacts that occurred in certain scenarios |
| 🐛 Bug Fix | Improved screen transition smoothness |
| ⚡ Performance | Reduced firmware size from 8.0MB to 5.2MB |

**Known Issues:**
- None reported

---

### 📦 Version 1.0 (Factory)

**Initial Release**

This is the factory firmware that ships with the XIAO Debug Mate.

**Features:**
- ✅ DAPLink debugger functionality
- ✅ UART bridge with configurable baud rate
- ✅ Real-time power monitoring
- ✅ LVGL-based graphical user interface
- ✅ Rotary encoder navigation
- ✅ Boot animation

**Known Issues:**
- ⚠️ Display ghosting may occur in some scenarios (fixed in v1.1)

---

## ⚠️ Troubleshooting

### Port Not Found

**macOS:**
```bash
ls /dev/cu.usb*
```

**Linux:**
```bash
ls /dev/ttyUSB* /dev/ttyACM*
```

**Windows:**
Check Device Manager for COM port number.

### Permission Denied (Linux)

```bash
sudo usermod -a -G dialout $USER
# Log out and log back in
```

### Device Not in Download Mode

1. Disconnect USB
2. Hold BOOT button
3. Connect USB while holding BOOT
4. Release BOOT button
5. Run flash script

### Flash Failed

1. Try a different USB cable (use data cable, not charge-only)
2. Try a different USB port
3. Reduce baud rate:
   ```bash
   esptool.py --chip esp32s3 --baud 115200 \
     --before default_reset --after hard_reset write_flash -z \
     --flash_mode keep --flash_freq keep --flash_size keep \
     0x10000 firmware-v1.1.bin
   ```

## 🔄 Downgrade

To downgrade to a previous version, simply flash the older firmware:

```bash
esptool.py --chip esp32s3 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z \
  --flash_mode keep --flash_freq keep --flash_size keep \
  0x10000 firmware-v1.0.bin
```

## 📊 Firmware Comparison

| Feature | v1.0 | v1.1 |
|---------|------|------|
| DAPLink | ✅ | ✅ |
| UART Bridge | ✅ | ✅ |
| Power Monitor | ✅ | ✅ |
| Display UI | Basic | ✨ Improved |
| Ghosting Fix | ❌ | ✅ |
| File Size | 8.0 MB | 5.2 MB |

