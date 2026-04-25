# Índice de Documentación - Rtaiz

Bienvenido a Rtaiz. Este es tu punto de partida para acceder a toda la documentación.

## 📚 Documentación por Nivel

### 🚀 PRINCIPIANTE (Inicia aquí)

1. **[QUICK_START.md](QUICK_START.md)** ← **COMIENZA AQUÍ**
   - Comandos básicos para compilar y ejecutar
   - Instrucciones Linux y Windows
   - Tareas en VS Code
   - Debugging básico

2. **[README.md](README.md)** 
   - Descripción completa del proyecto
   - Estructura general
   - Dependencias
   - Instalación y compilación

3. **[.vscode/DEBUGGING.md](.vscode/DEBUGGING.md)**
   - Cómo debuggear en VS Code
   - Primeros pasos con GDB
   - Breakpoints y variables

### 🔧 INTERMEDIO (Desarrollo activo)

1. **[CMAKE_GUIDE.md](CMAKE_GUIDE.md)**
   - Cómo funciona CMake
   - Estructura jerárquica
   - Conceptos como target_link_libraries
   - Cómo agregar módulos nuevos

2. **[CHECKLIST.md](CHECKLIST.md)**
   - Verificar que todo está funcional
   - Paso a paso de las pruebas
   - Troubleshooting básico

### 👨‍💻 AVANZADO (Cuando tienes dudas)

- Archivos CMakeLists.txt en cada módulo
- Código fuente: [phobos/*/src/](phobos/)
- Configuración de VS Code: [.vscode/](vscode/)

## 📖 Documentación por Tema

### Compilación y Build

| Tema | Archivo | Sección |
|------|---------|---------|
| Compilar rápidamente | [QUICK_START.md](QUICK_START.md) | Inicio Rápido |
| Release vs Debug | [QUICK_START.md](QUICK_START.md) | Compilación Release |
| Estructura CMake | [CMAKE_GUIDE.md](CMAKE_GUIDE.md) | Visión General |
| Agregar dependencias | [CMAKE_GUIDE.md](CMAKE_GUIDE.md) | Agregar Dependencia Externa |

### Debugging

| Tema | Archivo | Sección |
|------|---------|---------|
| Empezar a debuggear | [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md) | Primer uso |
| Debugging paso a paso | [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md) | Debugging Paso a Paso |
| Breakpoints | [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md) | Puntos de Interrupción |
| GDB manual | [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md) | Terminal integrada |

### Desarrollo

| Tema | Archivo | Sección |
|------|---------|---------|
| Agregar módulo nuevo | [CMAKE_GUIDE.md](CMAKE_GUIDE.md) | Agregar Nuevo Módulo |
| Agregar dependencia externa | [CMAKE_GUIDE.md](CMAKE_GUIDE.md) | Agregar Dependencia Externa |
| Entender dependencias | [CMAKE_GUIDE.md](CMAKE_GUIDE.md) | Arquitectura de Dependencias |
| Tareas VS Code | [QUICK_START.md](QUICK_START.md) | Tareas disponibles en VS Code |

### Troubleshooting

| Problema | Solución |
|----------|----------|
| CMake no configura | [CHECKLIST.md](CHECKLIST.md) → Problema: Algo No Funciona #1 |
| Errores de compilación | [CHECKLIST.md](CHECKLIST.md) → Problema: Algo No Funciona #2 |
| Librerías no encontradas | [CHECKLIST.md](CHECKLIST.md) → Problema: Algo No Funciona #3 |
| IntelliSense no funciona | [CHECKLIST.md](CHECKLIST.md) → Problema: Algo No Funciona #4 |
| GDB no funciona | [CHECKLIST.md](CHECKLIST.md) → Problema: Algo No Funciona #5 |

## 🗂️ Estructura del Proyecto

```
rtaiz/
├── 📄 QUICK_START.md          ← Comienza aquí para compilar
├── 📄 README.md               ← Documentación completa
├── 📄 CMAKE_GUIDE.md          ← Entiende la estructura
├── 📄 CHECKLIST.md            ← Verifica que todo funciona
│
├── CMakeLists.txt             ← Configuración Build
├── CMakePresets.json          ← Presets de compilación
│
├── phobos/
│   ├── CMakeLists.txt         ← Agrupa todos los módulos
│   ├── common/                ← Módulo base
│   ├── window/                ← Gestión de ventanas
│   ├── sound/                 ← Gestión de audio
│   ├── io/                    ← Entrada/salida
│   └── graphics/              ← Renderización con GLM
│
├── game/
│   ├── CMakeLists.txt         ← Configuración ejecutable
│   └── src/
│       └── main.cpp           ← Punto de entrada
│
├── .vscode/
│   ├── 📄 DEBUGGING.md        ← Guía de debugging
│   ├── launch.json            ← Configuración F5
│   ├── tasks.json             ← Tareas Ctrl+Shift+B
│   ├── settings.json          ← Configuración editor
│   ├── c_cpp_properties.json  ← IntelliSense
│   └── extensions.json        ← Extensiones recomendadas
│
├── 🔧 build.sh                ← Compilar en Linux
├── 🔧 build.bat               ← Compilar en Windows
└── .gitignore                 ← Ignorar archivos Git
```

## 🎯 Flujos de Trabajo Comunes

### Flujo 1: Primer Tiempo (5-10 minutos)

1. Abre [QUICK_START.md](QUICK_START.md)
2. Ejecuta el comando de compilación (Linux o tu plataforma)
3. Ejecuta el programa
4. Presiona Ctrl+C para salir

### Flujo 2: Debuggear en VS Code (2-3 minutos)

1. Abre el proyecto en VS Code
2. Lee [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md)
3. Presiona F5
4. Elige "Debug Game (Linux GDB)" o Windows equivalente

### Flujo 3: Entender la Estructura (10-15 minutos)

1. Lee [README.md](README.md)
2. Lee [CMAKE_GUIDE.md](CMAKE_GUIDE.md)
3. Explora archivos CMakeLists.txt
4. Mira el código en [phobos/*/src/](phobos/)

### Flujo 4: Agregar Nuevo Módulo (15-20 minutos)

1. Lee [CMAKE_GUIDE.md](CMAKE_GUIDE.md) → "Agregar Nuevo Módulo"
2. Copia estructura de [phobos/common/](phobos/common/) a tu módulo
3. Actualiza [phobos/CMakeLists.txt](phobos/CMakeLists.txt)
4. Compila: `./build.sh debug`

### Flujo 5: Agregar Dependencia Externa (10 minutos)

1. Lee [CMAKE_GUIDE.md](CMAKE_GUIDE.md) → "Agregar Dependencia Externa"
2. Edita el CMakeLists.txt del módulo
3. Agrega FetchContent_Declare y FetchContent_MakeAvailable
4. Recompila

### Flujo 6: Verificar Todo Funciona (5-10 minutos)

1. Lee [CHECKLIST.md](CHECKLIST.md)
2. Marca puntos a medida que verificas
3. Si algo falla, ve a "Problema: Algo No Funciona"

## 🔗 Enlaces Rápidos

### Al Código Fuente
- [common.hpp - Módulo base](phobos/common/include/phobos/common/common.hpp)
- [window.hpp - Ventanas](phobos/window/include/phobos/window/window.hpp)
- [sound.hpp - Audio](phobos/sound/include/phobos/sound/sound.hpp)
- [io.hpp - I/O](phobos/io/include/phobos/io/io.hpp)
- [graphics.hpp - Gráficos](phobos/graphics/include/phobos/graphics/graphics.hpp)
- [main.cpp - Programa principal](game/src/main.cpp)

### A Configuración
- [Configuración principal CMake](CMakeLists.txt)
- [Configuración phobos](phobos/CMakeLists.txt)
- [Configuración game](game/CMakeLists.txt)
- [Presets CMake](CMakePresets.json)
- [Tareas VS Code](.vscode/tasks.json)
- [Debugging VS Code](.vscode/launch.json)

## 📱 Plataformas

### Linux x64 (GCC/Clang)
- Documentación: [QUICK_START.md](QUICK_START.md) - Linux
- Build: [build.sh](build.sh)
- Debugging: [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md) - En Linux

### Windows Visual Studio 2025
- Documentación: [QUICK_START.md](QUICK_START.md) - Windows
- Build: [build.bat](build.bat)
- Debugging: [.vscode/(launch.json](.vscode/launch.json) - Windows MSVC

## 💡 Tips Rápidos

```bash
# Compilar y ejecutar en una línea
cd /home/ismael/Game/rtaiz && ./build.sh debug && ./build/linux-debug/bin/game

# Debuggear con GDB manualmente
cd /home/ismael/Game/rtaiz/build/linux-debug/bin
LD_LIBRARY_PATH=. gdb ./game

# Ver tareas en VS Code
Ctrl+Shift+B

# Debuggear en VS Code
F5

# Compilar Release (más rápido)
./build.sh release

# Limpiar archivos de compilación
rm -rf build CMakeCache.txt CMakeFiles
```

## 🎓 Orden Recomendado de Lectura

1. **Este archivo** (índice)
2. **[QUICK_START.md](QUICK_START.md)** - Compila y ejecuta
3. **[README.md](README.md)** - Entiende el proyecto
4. **[.vscode/DEBUGGING.md](.vscode/DEBUGGING.md)** - Aprende a debuggear
5. **[CMAKE_GUIDE.md](CMAKE_GUIDE.md)** - Entiende CMake
6. **[CHECKLIST.md](CHECKLIST.md)** - Verifica todo
7. Explora el código fuente

## ❓ Preguntas Frecuentes

**P: ¿Por dónde empiezo?**
R: Lee [QUICK_START.md](QUICK_START.md) primer.

**P: ¿Cómo debuggeo?**
R: Presiona F5 o lee [.vscode/DEBUGGING.md](.vscode/DEBUGGING.md).

**P: ¿Cómo agrego un módulo?**
R: Lee [CMAKE_GUIDE.md](CMAKE_GUIDE.md) - "Agregar Nuevo Módulo".

**P: ¿Cómo agrego una dependencia?**
R: Lee [CMAKE_GUIDE.md](CMAKE_GUIDE.md) - "Agregar Dependencia Externa".

**P: Algo no funciona, ¿qué hago?**
R: Lee [CHECKLIST.md](CHECKLIST.md) - "Problema: Algo No Funciona".

## 📝 Versión y Actualizaciones

- **Versión**: 1.0
- **Fecha**: 25 de abril de 2026
- **Estados**: Proyecto completo y funcional
- **Plataformas**: Linux x64 ✓, Windows x64 ✓

---

**¡Bienvenido a Rtaiz!** 🎮

Comienza con [QUICK_START.md](QUICK_START.md) para compilar tu primer build.
