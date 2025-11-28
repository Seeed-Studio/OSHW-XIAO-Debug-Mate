#!/bin/bash

#############################################
#  XIAO Debug Mate - Firmware Flash Script
#  Automatically flashes the latest firmware
#############################################

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo ""
echo -e "${CYAN}╔═══════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║      🔧 XIAO Debug Mate - Firmware Flasher        ║${NC}"
echo -e "${CYAN}╚═══════════════════════════════════════════════════╝${NC}"
echo ""

# Find the latest firmware file
echo -e "${BLUE}🔍 Scanning for firmware files...${NC}"
LATEST_FIRMWARE=""
LATEST_VERSION="0.0"

for file in firmware-v*.bin; do
    if [[ -f "$file" ]]; then
        # Extract version number (e.g., "1.1" from "firmware-v1.1.bin")
        VERSION=$(echo "$file" | sed -E 's/firmware-v([0-9]+\.[0-9]+)\.bin/\1/')
        
        echo -e "   Found: ${YELLOW}$file${NC} (v$VERSION)"
        
        # Parse major and minor version
        V1_MAJOR=$(echo "$VERSION" | cut -d. -f1)
        V1_MINOR=$(echo "$VERSION" | cut -d. -f2)
        V2_MAJOR=$(echo "$LATEST_VERSION" | cut -d. -f1)
        V2_MINOR=$(echo "$LATEST_VERSION" | cut -d. -f2)
        
        if [[ $V1_MAJOR -gt $V2_MAJOR ]] || [[ $V1_MAJOR -eq $V2_MAJOR && $V1_MINOR -gt $V2_MINOR ]]; then
            LATEST_VERSION="$VERSION"
            LATEST_FIRMWARE="$file"
        fi
    fi
done

# Check if any firmware was found
if [[ -z "$LATEST_FIRMWARE" ]]; then
    echo ""
    echo -e "${RED}❌ Error: No firmware files found!${NC}"
    echo -e "   Please ensure firmware-v*.bin files exist in this directory."
    echo ""
    read -p "Press Enter to exit..."
    exit 1
fi

echo ""
echo -e "${GREEN}✅ Latest firmware: ${YELLOW}$LATEST_FIRMWARE${NC} (v$LATEST_VERSION)"
echo ""

# Check if esptool is installed
echo -e "${BLUE}🔍 Checking for esptool...${NC}"
if command -v esptool.py &> /dev/null; then
    ESPTOOL="esptool.py"
elif command -v esptool &> /dev/null; then
    ESPTOOL="esptool"
else
    echo ""
    echo -e "${RED}❌ Error: esptool not found!${NC}"
    echo ""
    echo -e "   Please install esptool using:"
    echo -e "   ${CYAN}pip install esptool${NC}"
    echo ""
    read -p "Press Enter to exit..."
    exit 1
fi
echo -e "   Using: ${GREEN}$ESPTOOL${NC}"
echo ""

# Auto-detect serial port
echo -e "${BLUE}🔍 Detecting serial port...${NC}"
PORT=""

# macOS: look for cu.usbmodem* or cu.usbserial*
if [[ "$(uname)" == "Darwin" ]]; then
    for p in /dev/cu.usbmodem* /dev/cu.usbserial* /dev/cu.wchusbserial*; do
        if [[ -e "$p" ]]; then
            PORT="$p"
            break
        fi
    done
# Linux: look for ttyUSB* or ttyACM*
else
    for p in /dev/ttyUSB* /dev/ttyACM*; do
        if [[ -e "$p" ]]; then
            PORT="$p"
            break
        fi
    done
fi

if [[ -z "$PORT" ]]; then
    echo -e "${YELLOW}⚠️  No serial port auto-detected. esptool will try to find it.${NC}"
    PORT_ARG=""
else
    echo -e "   Found: ${GREEN}$PORT${NC}"
    PORT_ARG="--port \"$PORT\""
fi
echo ""

# Prompt user to continue
echo -e "${YELLOW}⚡ Ready to flash firmware${NC}"
echo ""
echo "   Make sure:"
echo "   1. XIAO Debug Mate is connected via USB-C"
echo "   2. Device is in download mode (hold BOOT, press RESET)"
echo ""
read -p "Press Enter to start flashing (or Ctrl+C to cancel)..."
echo ""

# Flash the firmware
echo -e "${BLUE}🚀 Flashing ${YELLOW}$LATEST_FIRMWARE${BLUE}...${NC}"
echo ""

if [[ -z "$PORT" ]]; then
    $ESPTOOL --chip esp32s3 \
        --baud 921600 \
        --before default_reset \
        --after hard_reset \
        write_flash -z \
        --flash_mode keep \
        --flash_freq keep \
        --flash_size keep \
        0x10000 "$LATEST_FIRMWARE"
else
    $ESPTOOL --chip esp32s3 \
        --port "$PORT" \
        --baud 921600 \
        --before default_reset \
        --after hard_reset \
        write_flash -z \
        --flash_mode keep \
        --flash_freq keep \
        --flash_size keep \
        0x10000 "$LATEST_FIRMWARE"
fi

# Check result
if [[ $? -eq 0 ]]; then
    echo ""
    echo -e "${GREEN}╔═══════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║         ✅ Flash completed successfully!          ║${NC}"
    echo -e "${GREEN}╚═══════════════════════════════════════════════════╝${NC}"
    echo ""
    echo -e "   Firmware: ${CYAN}$LATEST_FIRMWARE${NC}"
    echo -e "   Version:  ${CYAN}v$LATEST_VERSION${NC}"
    echo ""
    echo -e "   ${YELLOW}The device will automatically reset and start running.${NC}"
else
    echo ""
    echo -e "${RED}╔═══════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║              ❌ Flash failed!                     ║${NC}"
    echo -e "${RED}╚═══════════════════════════════════════════════════╝${NC}"
    echo ""
    echo "   Troubleshooting:"
    echo "   1. Make sure the device is in download mode"
    echo "   2. Try a different USB cable or port"
    echo "   3. Check if the correct drivers are installed"
fi

echo ""
read -p "Press Enter to exit..."
