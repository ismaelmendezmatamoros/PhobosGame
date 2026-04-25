# Script para configurar y compilar el proyecto en Linux

#!/bin/bash

set -e

echo "=== Rtaiz Build Script (Linux) ==="
echo ""

# Detectar modo
MODE=${1:-debug}

if [[ "$MODE" != "debug" && "$MODE" != "release" ]]; then
    echo "Uso: ./build.sh [debug|release]"
    exit 1
fi

BUILD_DIR="build/linux-${MODE}"
CMAKE_BUILD_TYPE=$(echo "$MODE" | tr '[:lower:]' '[:upper:]')

echo "Configuración: $CMAKE_BUILD_TYPE"
echo "Directorio de compilación: $BUILD_DIR"
echo ""

# Crear directorio si no existe
mkdir -p "$BUILD_DIR"

# Configurar CMake
echo "Configurando CMake..."
cmake -B "$BUILD_DIR" \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_C_COMPILER=gcc

echo ""
echo "Compilando..."
cmake --build "$BUILD_DIR" --parallel $(nproc)

echo ""
echo "¡Compilación completada!"
echo ""
echo "Ejecutar el juego con:"
echo "  ./$BUILD_DIR/bin/game"
