@echo off

REM Define paths
set PROGRAMMER_CLI="C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"

REM Define files and addresses
set BINARY=%~dp0build\lv_stm32f769.elf

REM Flashing the signed binary
%PROGRAMMER_CLI% -c port=SWD mode=normal -d %BINARY% -s