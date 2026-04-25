# Guía Rápida de Desarrollo - Rtaiz

## 🚀 Inicio Rápido

### Linux (Recomendado para desarrollo inicial)

```bash
cd /home/ismael/Game/rtaiz

# Opción 1: Usar el script
chmod +x build.sh
./build.sh debug      # Compila en modo Debug
./build.sh release    # Compila en modo Release

# Opción 2: Comandos manuales
cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build/linux-debug
./build/linux-debug/bin/game
```

### Windows (Visual Studio 2025)

```cmd
cd C:\path\to\rtaiz

# Opción 1: Usar el script
build.bat debug       # Compila en modo Debug
build.bat release     # Compila en modo Release

# Opción 2: Comandos manuales
cmake -B build\windows-debug -G "Visual Studio 17 2025" -DCMAKE_BUILD_TYPE=Debug
cmake --build build\windows-debug --config Debug
.\build\windows-debug\bin\Debug\game.exe
```

## 📁 Estructura de Directorios

```
rtaiz/
├── phobos/                # Motor del juego
│   ├── common/           # Módulo base
│   ├── window/           # Gestión de ventanas
│   ├── sound/            # Audio
│   ├── io/               # Entrada/salida
│   └── graphics/         # Renderización (con GLM)
│
├── game/                 # Aplicación del juego
│   └── src/main.cpp
│
├── build/                # Directorios de compilación (auto-generados)
│   ├── linux-debug/
│   ├── linux-release/
│   ├── windows-debug/
│   └── windows-release/
│
├── .vscode/              # Configuración VS Code
│   ├── tasks.json        # Tareas de compilación
│   ├── launch.json       # Configuración de debugging
│   ├── settings.json     # Preferencias del editor
│   ├── c_cpp_properties.json  # IntelliSense
│   └── extensions.json   # Extensiones recomendadas
│
├── CMakeLists.txt        # CMake principal
├── CMakePresets.json     # Presets de CMake
├── build.sh              # Script de compilación Linux
├── build.bat             # Script de compilación Windows
├── README.md             # Documentación completaigualmente
└── .gitignore            # Archivos a ignorar en git
```

## 🔧 Tareas en VS Code

Presiona `Ctrl+Shift+B` para ver todas las tareas:

### Compilación
- **CMake: Configure (Linux Debug)** - Configura el proyecto
- **CMake: Build (Linux Debug)** - Compila
- **Build & Run Game (Linux Debug)** - Compila y ejecuta

### Limpieza
- **Clean Build Artifacts** - Elimina archivos de compilación

### Windows
- **CMake: Build (Windows MSVC Debug)** - Configura Windows
- **CMake: Build Project (Windows MSVC Debug)** - Compila Windows

## 🐛 Debugging

### VS Code
Presiona `F5` o `Run > Start Debugging` y selecciona:
- **Debug Game (Linux GDB)** - Para Linux con GDB
- **Release Game (Linux GDB)** - Para builds Release
- **Debug Game (Windows MSVC)** - Para Windows MSVC

### Manual con GDB
```bash
cd /home/ismael/Game/rtaiz/build/linux-debug/bin
LD_LIBRARY_PATH=. gdb ./game
(gdb) run
(gdb) break main
```

## 📦 Dependencias do Proyecto

```
game (ejecutable)
  └─ phobos (agrupa)
      ├─ phobos_common (librería compartida)
      ├─ phobos_window (→ common)
      ├─ phobos_sound (→ common)
      ├─ phobos_io (→ common)
      └─ phobos_graphics (→ window, common, GLM)
```

## ➕ Agregar Nuevas Dependencias Externas

### Ejemplo: Agregar GLFW a window

Editar `phobos/window/CMakeLists.txt`:

```cmake
# Después de include(FetchContent)
FetchContent_Declare(glfw
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
)
FetchContent_MakeAvailable(glfw)

# En target_link_libraries
target_link_libraries(phobos_window
    PUBLIC phobos_common glfw
)
```

## 🏗️ Compilación Multi-Configuración

```bash
# Debug + Release
./build.sh debug
./build.sh release

# Ejecutar ambas versiones
./build/linux-debug/bin/game    # ~134 KB (no optimizado)
./build/linux-release/bin/game  # ~89 KB (optimizado)
```

## 🔍 Variables de Entorno

Para ejecutar sin instalar librerías:

```bash
export LD_LIBRARY_PATH=/home/ismael/Game/rtaiz/build/linux-debug/lib:$LD_LIBRARY_PATH
./build/linux-debug/bin/game
```

## 📝 Desarrollar Nuevos Módulos

1. Crear carpeta: `phobos/my_module/`
2. Crear estructura:
   ```
   my_module/
   ├── include/phobos/my_module/
   │   └── my_module.hpp
   ├── src/
   │   └── my_module.cpp
   └── CMakeLists.txt
   ```

3. Crear `CMakeLists.txt` (basado en otros módulos)
4. Agregar a `phobos/CMakeLists.txt`:
   ```cmake
   add_subdirectory(my_module)
   target_link_libraries(phobos INTERFACE phobos_my_module)
   ```

## 🎯 Comandos Útiles

```bash
# Ver estructura de compilación
tree build/linux-debug/bin
tree build/linux-debug/lib

# Limpiar completamente
rm -rf build CMakeCache.txt CMakeFiles

# Ver información de la configuración
cat build/linux-debug/CMakeCache.txt | grep CMAKE_BUILD_TYPE

# Configurar solo (sin compilar)
cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug

# Compilar en paralelo (más rápido)
cmake --build build/linux-debug --parallel $(nproc)

# Instalar en directorio específico
cmake --install build/linux-debug --prefix ./install
```

## ⚙️ Configuración de Compiladores

### Linux (cambiar compilador)
```bash
cmake -B build/linux-debug \
    -G "Unix Makefiles" \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_BUILD_TYPE=Debug
```

### Windows (cambiar generador)
```cmd
# Usar Ninja en lugar de Visual Studio
cmake -B build\windows-ninja -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build build\windows-ninja
```

## 🧹 Troubleshooting

### ¿Problema con GLM no encontrado?
- El proyecto descarga GLM automáticamente con FetchContent
- Ubicación: `build/linux-debug/_deps/glm-src/`
- GeneralmenteCMake se encarga de todo

### ¿Librerías no encontradas (LD_LIBRARY_PATH)?
```bash
export LD_LIBRARY_PATH=/home/ismael/Game/rtaiz/build/linux-debug/lib:$LD_LIBRARY_PATH
```

### ¿Limpiar cache de CMake?
```bash
rm -rf build CMakeCache.txt CMakeFiles
cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

### ¿Regenerar IntelliSense en VS Code?
- Presiona `Ctrl+Shift+P`
- Escribe "C/C++: Rescan Solution"

## 📚 Recursos

- [CMake Documentation](https://cmake.org/documentation/)
- [GLM Documentation](https://github.com/g-truc/glm/wiki)
- [VS Code C++ Guide](https://code.visualstudio.com/docs/languages/cpp)
- [GDB Documentation](https://sourceware.org/gdb/documentation/)
