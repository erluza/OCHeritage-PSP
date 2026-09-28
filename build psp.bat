@echo off
setlocal enabledelayedexpansion
cd /d "%~dp0"

if /I "%~1"=="clean" (
    echo Cleaning PSP build directory...
    wsl.exe -d Ubuntu bash -c "cd '$(wslpath '%CD%')' && rm -rf build/psp"
    echo Clean complete.
    exit /b 0
)

echo ===================================================
echo   OptiCraft Heritage Edition: PSP Build (WSL)
echo ===================================================

wsl.exe -d Ubuntu bash -c "cd '$(wslpath '%CD%')' && bash ./build_psp.sh"
if errorlevel 1 (
    echo [ERROR] Build failed!
    exit /b 1
)

if exist "C:\Users\user\Downloads\ppsspp\memstick\PSP\GAME\OptiCraft" (
    copy /Y "EBOOT.PBP" "C:\Users\user\Downloads\ppsspp\memstick\PSP\GAME\OptiCraft\EBOOT.PBP" >nul
    echo [OK] EBOOT.PBP deployed to PPSSPP memstick.
)
if exist "C:\Users\user\Downloads\PPSSPP-v1.20.4-Windows-x64\memstick\PSP\GAME\OptiCraft" (
    copy /Y "EBOOT.PBP" "C:\Users\user\Downloads\PPSSPP-v1.20.4-Windows-x64\memstick\PSP\GAME\OptiCraft\EBOOT.PBP" >nul
    echo [OK] EBOOT.PBP deployed to PPSSPP-v1.20.4 memstick.
)
if exist "C:\Users\user\Documents\PPSSPP\PSP\GAME\OptiCraft" (
    copy /Y "EBOOT.PBP" "C:\Users\user\Documents\PPSSPP\PSP\GAME\OptiCraft\EBOOT.PBP" >nul
    echo [OK] EBOOT.PBP deployed to Documents PPSSPP.
)

echo ===================================================
echo   Build and deployment successful!
echo ===================================================
