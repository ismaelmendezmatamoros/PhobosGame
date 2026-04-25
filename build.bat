@echo off
REM Script para configurar y compilar el proyecto en Windows con Visual Studio 2025

setlocal enabledelayedexpansion

echo === Rtaiz Build Script (Windows) ===
echo.

REM Detectar modo
set MODE=%1
if "%MODE%"=="" set MODE=debug

if /i not "%MODE%"=="debug" if /i not "%MODE%"=="release" (
    echo Uso: build.bat [debug^|release]
    exit /b 1
)

set BUILD_DIR=build\windows-%MODE%
if /i "%MODE%"=="debug" (
    set CMAKE_BUILD_TYPE=Debug
) else (
    set CMAKE_BUILD_TYPE=Release
)

echo Configuracion: %CMAKE_BUILD_TYPE%
echo Directorio de compilacion: %BUILD_DIR%
echo.

REM Crear directorio si no existe
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

REM Configurar CMake
echo Configurando CMake...
cmake -B "%BUILD_DIR%" ^
    -G "Visual Studio 17 2025" ^
    -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE%

if errorlevel 1 (
    echo Error en la configuracion de CMake
    exit /b 1
)

echo.
echo Compilando...
cmake --build "%BUILD_DIR%" --config %CMAKE_BUILD_TYPE% --parallel

if errorlevel 1 (
    echo Error en la compilacion
    exit /b 1
)

echo.
echo ¡Compilacion completada!
echo.
echo Ejecutar el juego con:
echo   .\%BUILD_DIR%\bin\%CMAKE_BUILD_TYPE%\game.exe
