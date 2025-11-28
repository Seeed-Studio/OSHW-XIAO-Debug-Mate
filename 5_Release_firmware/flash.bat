@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

REM ############################################
REM  XIAO Debug Mate - Firmware Flash Script
REM  Automatically flashes the latest firmware
REM ############################################

title XIAO Debug Mate - Firmware Flasher

echo.
echo ╔═══════════════════════════════════════════════════╗
echo ║      🔧 XIAO Debug Mate - Firmware Flasher        ║
echo ╚═══════════════════════════════════════════════════╝
echo.

REM Change to script directory
cd /d "%~dp0"

REM Find the latest firmware file
echo 🔍 Scanning for firmware files...

set "LATEST_FIRMWARE="
set "LATEST_MAJOR=0"
set "LATEST_MINOR=0"
set "LATEST_VERSION=0.0"

for %%F in (firmware-v*.bin) do (
    if exist "%%F" (
        set "FILENAME=%%~nF"
        REM Extract version from filename (firmware-v1.1 -> 1.1)
        set "VERSION=!FILENAME:firmware-v=!"
        
        echo    Found: %%F ^(v!VERSION!^)
        
        REM Parse major and minor version
        for /f "tokens=1,2 delims=." %%a in ("!VERSION!") do (
            set "CURR_MAJOR=%%a"
            set "CURR_MINOR=%%b"
        )
        
        REM Compare versions
        set /a "IS_NEWER=0"
        if !CURR_MAJOR! GTR !LATEST_MAJOR! (
            set /a "IS_NEWER=1"
        ) else if !CURR_MAJOR! EQU !LATEST_MAJOR! (
            if !CURR_MINOR! GTR !LATEST_MINOR! (
                set /a "IS_NEWER=1"
            )
        )
        
        if !IS_NEWER! EQU 1 (
            set "LATEST_MAJOR=!CURR_MAJOR!"
            set "LATEST_MINOR=!CURR_MINOR!"
            set "LATEST_VERSION=!VERSION!"
            set "LATEST_FIRMWARE=%%F"
        )
    )
)

REM Check if any firmware was found
if "%LATEST_FIRMWARE%"=="" (
    echo.
    echo ❌ Error: No firmware files found!
    echo    Please ensure firmware-v*.bin files exist in this directory.
    echo.
    pause
    exit /b 1
)

echo.
echo ✅ Latest firmware: %LATEST_FIRMWARE% ^(v%LATEST_VERSION%^)
echo.

REM Check if esptool is available
echo 🔍 Checking for esptool...

set "ESPTOOL="

REM Check for esptool.exe in current directory
if exist "esptool.exe" (
    set "ESPTOOL=esptool.exe"
    goto :found_esptool
)

REM Check for esptool in PATH
where esptool.exe >nul 2>&1
if %errorlevel% equ 0 (
    set "ESPTOOL=esptool.exe"
    goto :found_esptool
)

REM Check for esptool.py in PATH (Python installation)
where esptool.py >nul 2>&1
if %errorlevel% equ 0 (
    set "ESPTOOL=esptool.py"
    goto :found_esptool
)

REM Check for esptool via Python
python -m esptool version >nul 2>&1
if %errorlevel% equ 0 (
    set "ESPTOOL=python -m esptool"
    goto :found_esptool
)

echo.
echo ❌ Error: esptool not found!
echo.
echo    Please install esptool using:
echo    pip install esptool
echo.
pause
exit /b 1

:found_esptool
echo    Using: %ESPTOOL%
echo.

REM Prompt user to continue
echo ⚡ Ready to flash firmware
echo.
echo    Make sure:
echo    1. XIAO Debug Mate is connected via USB-C
echo    2. Device is in download mode ^(hold BOOT, press RESET^)
echo.
pause

echo.
echo 🚀 Flashing %LATEST_FIRMWARE%...
echo.

REM Flash the firmware with correct parameters
%ESPTOOL% --chip esp32s3 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x10000 "%LATEST_FIRMWARE%"

REM Check result
if %errorlevel% equ 0 (
    echo.
    echo ╔═══════════════════════════════════════════════════╗
    echo ║         ✅ Flash completed successfully!          ║
    echo ╚═══════════════════════════════════════════════════╝
    echo.
    echo    Firmware: %LATEST_FIRMWARE%
    echo    Version:  v%LATEST_VERSION%
    echo.
    echo    The device will automatically reset and start running.
) else (
    echo.
    echo ╔═══════════════════════════════════════════════════╗
    echo ║              ❌ Flash failed!                     ║
    echo ╚═══════════════════════════════════════════════════╝
    echo.
    echo    Troubleshooting:
    echo    1. Make sure the device is in download mode
    echo    2. Try a different USB cable or port
    echo    3. Check if the correct drivers are installed
)

echo.
pause
