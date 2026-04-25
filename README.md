# Rtaiz - Game Engine & Game

Un motor de juegos moderno en C++ 23 con CMake para plataformas Linux (x64) y Windows (Visual Studio 2025).

## Estructura del Proyecto

```
rtaiz/
├── phobos/                 # Motor de juegos (librería)
│   ├── common/            # Módulo común (base para otros)
│   ├── window/            # Gestión de ventanas
│   ├── sound/             # Gestión de audio
│   ├── io/                # Entrada/salida y sistema de archivos
│   └── graphics/          # Renderización (con GLM)
│
└── game/                  # Aplicación de juego
    └── src/
        └── main.cpp       # Punto de entrada
```

## Dependencias

- **C++ 23**
- **CMake 3.22+**
- **GLM** (se descarga automáticamente)
- **g++** / **clang** (Linux) o **MSVC** (Windows)

## Configuración

### Linux

#### Configurar (Debug)
```bash
cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

#### Compilar (Debug)
```bash
cmake --build build/linux-debug
```

#### Ejecutar
```bash
./build/linux-debug/bin/game
```

### Windows (Visual Studio 2025)

#### Configurar (Debug)
```cmd
cmake -B build/windows-debug -G "Visual Studio 17 2025" -DCMAKE_BUILD_TYPE=Debug
```

#### Compilar (Debug)
```cmd
cmake --build build/windows-debug --config Debug
```

#### Ejecutar
```cmd
.\build\windows-debug\bin\Debug\game.exe
```

## Debugging desde VS Code

### Linux (GDB)
1. Presiona `F5` o ve a Run > Start Debugging
2. Selecciona "Debug Game (Linux GDB)"
3. VS Code compilará automáticamente si es necesario

### Windows (MSVC)
1. Presiona `F5` o ve a Run > Start Debugging
2. Selecciona "Debug Game (Windows MSVC)"

## Tareas disponibles en VS Code

Accede a ellas con `Ctrl+Shift+B`:

- **CMake: Configure (Linux Debug)** - Configura el proyecto para Linux
- **CMake: Build (Linux Debug)** - Compila el proyecto
- **CMake: Configure (Linux Release)** - Configura en modo Release
- **CMake: Build (Linux Release)** - Compila en modo Release
- **Build & Run Game (Linux Debug)** - Compila y ejecuta en una sola tarea
- **Clean Build Artifacts** - Limpia los archivos de compilación
- **CMake: Build (Windows MSVC Debug)** - Configura para Windows
- **CMake: Build Project (Windows MSVC Debug)** - Compila para Windows

## Agregar Dependencias Externas

Cada módulo puede agregar dependencias externas usando FetchContent. Por ejemplo, para agregar GLFW a window:

En `phobos/window/CMakeLists.txt`:

```cmake
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

target_link_libraries(phobos_window PUBLIC glfw)
```

## Arquitectura de Dependencias

```
phobos (librería agregada)
  ├─ common (librería compartida)
  ├─ window (librería compartida) → depende de common
  ├─ sound (librería compartida) → depende de common
  ├─ io (librería compartida) → depende de common
  └─ graphics (librería compartida) → depende de window + common + GLM

game (ejecutable)
  └─ phobos (todas sus dependencias)
```

## Compilación Release

Para compilaciones de producción con optimizaciones:

### Linux
```bash
cmake -B build/linux-release -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build/linux-release
./build/linux-release/bin/game
```

### Windows
```cmd
cmake -B build/windows-release -G "Visual Studio 17 2025" -DCMAKE_BUILD_TYPE=Release
cmake --build build/windows-release --config Release
.\build\windows-release\bin\Release\game.exe
```

## IntelliSense y Desarrollo

Las configuraciones de VS Code incluyen:
- **c_cpp_properties.json** - Configuración de IntelliSense
- **settings.json** - Configuración del editor
- **CMakePresets.json** - Configuración de CMake
- **tasks.json** - Tareas personalizadas
- **launch.json** - Configuración de debugging

## Instalación

```bash
cmake --install build/linux-debug --prefix ./install
```

## Limpieza

```bash
rm -rf build cmake_install.cmake CMakeCache.txt CMakeFiles
```

## Licencia

Proyecto personal - 2026

## Notas

- Todas las librerías se compilan como librerías compartidas por defecto
- C++ Standard: C++ 23
- GLM se descarga automáticamente durante la configuración
- Soporte multiplataforma: Linux (x64) y Windows (x64, Visual Studio 2025)
