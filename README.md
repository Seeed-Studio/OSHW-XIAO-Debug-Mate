# Debugger

Here is the Debugger source code repository

## Dependencies

Libraries that must be downloaded

- DAPLink: https://github.com/Lesords/Seeed_Arduino_DAPLink/tree/feat/ESP32S3

- TFT: https://github.com/Lesords/TFT_eSPI/tree/feat/ST7789-EVT

- LVGL: https://github.com/Lesords/lvgl/tree/feat/Debugger

- INA: https://github.com/adafruit/Adafruit_INA228

- TinyUSB: https://github.com/adafruit/Adafruit_TinyUSB_Arduino

- I2C_EEPROM: https://github.com/RobTillaart/I2C_EEPROM

## Configuration items

The following configuration needs to be modified to the corresponding options

- `Partition Scheme` : "Maximum APP (7.9MB APP No OTA/No FS)"

- `PSRAM` : "OPI PSRAM"

- `USB Mode` : "USB-OTG (TinyUSB)"

## Installation

Download the following library in Arduino's library manager

- Adafruit INA228 Library, Recommended version: 2.0.1

- Adafruit TinyUSB Library, Recommended version: 3.4.4

Download the following libraries through the command line

```bash
# Go to the library directory
cd ~/Documents/Arduino/libraries

# DAPLink
git clone --depth 1 https://github.com/Lesords/Seeed_Arduino_DAPLink.git -b feat/ESP32S3

# TFT
git clone --depth 1 https://github.com/Lesords/TFT_eSPI.git -b feat/ST7789-EVT

# LVGL
git clone --depth 1 https://github.com/Lesords/lvgl.git -b feat/Debugger

# I2C_EEPROM (tag 1.9.4)
git clone https://github.com/RobTillaart/I2C_EEPROM.git

# Debugger
git clone --depth 1 https://github.com/Lesords/Debugger.git
```
