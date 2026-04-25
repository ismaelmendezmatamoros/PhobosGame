# Checklist de Verificación - Rtaiz

Usa esta lista para verificar que todo está funcionando correctamente.

## ✅ Instalación de Requisitos

- [ ] CMake 3.22 o superior instalado
  ```bash
  cmake --version
  ```

- [ ] g++ o clang++ instalado (Linux)
  ```bash
  g++ --version
  ```

- [ ] Visual Studio 2025 o MSVC instalado (Windows)
  ```cmd
  cl.exe
  ```

- [ ] GDB instalado para debugging (Linux)
  ```bash
  gdb --version
  ```

- [ ] VS Code instalado
  ```bash
  code --version
  ```

## ✅ Proyecto Descargado

- [ ] Carpeta rtaiz existe: `/home/ismael/Game/rtaiz/`

- [ ] Estructura completa:
  ```bash
  ls -la /home/ismael/Game/rtaiz/
  ```

- [ ] Esperar ver:
  - CMakeLists.txt
  - CMakePresets.json
  - phobos/
  - game/
  - .vscode/

## ✅ Configuración Inicial (Linux)

```bash
cd /home/ismael/Game/rtaiz
```

- [ ] Configuración exitosa:
  ```bash
  cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
  ```

- [ ] Debe decir al final:
  ```
  -- Configuring done
  -- Generating done
  ```

- [ ] Verificar que GLM se descargó:
  ```bash
  ls build/linux-debug/_deps/glm-src/glm/
  ```

## ✅ Compilación (Linux)

- [ ] Compilación sin errores:
  ```bash
  cmake --build build/linux-debug
  ```

- [ ] Debe decir al final:
  ```
  [100%] Built target game
  ```

- [ ] Verificar ejecutable:
  ```bash
  ls -lh build/linux-debug/bin/game
  file build/linux-debug/bin/game
  ```

- [ ] Verificar librerías:
  ```bash
  ls -lh build/linux-debug/lib/*.so*
  ```

## ✅ Ejecución del Ejecutable

- [ ] Ejecutar sin errores:
  ```bash
  cd /home/ismael/Game/rtaiz/build/linux-debug/bin
  LD_LIBRARY_PATH=. ./game
  ```

- [ ] Debe verse:
  ```
  === Phobos Game Engine ===
  Phobos version: 1.0.0
  Window created and shown
  Sound manager initialized: true
  File system ready
  Renderer initialized
  ```

- [ ] Presionar Ctrl+C para salir

## ✅ Configuración en VS Code

- [ ] Abrir la carpeta en VS Code:
  ```bash
  code /home/ismael/Game/rtaiz
  ```

- [ ] Se debe mostrar notificación de "Cargar extensiones recomendadas"
  - [ ] Aceptar

- [ ] CMake Tools debe ofrecer "Configure project"
  - [ ] Aceptar o ejecutar:
    - `Ctrl+Shift+P` → "CMake: Configure"

- [ ] Presionar `Ctrl+Shift+B` para ver tareas
  - [ ] Deben aparecer tareas de compilación

## ✅ Debugging en VS Code

- [ ] Presionar `F5` o `Run > Start Debugging`

- [ ] Elegir "Debug Game (Linux GDB)"

- [ ] El programa debe aparecer en la consola de debug

- [ ] Detener con `Shift+F5`

## ✅ Compilación en VS Code

- [ ] `Ctrl+Shift+B` → "CMake: Build (Linux Debug)"

- [ ] Debe compilar exitosamente en la terminal

- [ ] `Ctrl+Shift+B` → "Build & Run Game (Linux Debug)"

- [ ] Debe compilar y ejecutar el programa

## ✅ Archivos de Documentación

- [ ] Leer README.md:
  ```bash
  cat README.md
  ```

- [ ] Leer QUICK_START.md para desarrollo rápido

- [ ] Leer CMAKE_GUIDE.md para entender estructura

- [ ] Leer .vscode/DEBUGGING.md para debugging

## ✅ Compilación Release

- [ ] Compilar en modo Release (Linux):
  ```bash
  chmod +x build.sh
  ./build.sh release
  ```

- [ ] Ejecutar release:
  ```bash
  LD_LIBRARY_PATH=./build/linux-release/lib ./build/linux-release/bin/game
  ```

- [ ] Comparar tamaños (release debe ser más pequeño):
  ```bash
  ls -lh build/linux-debug/bin/game
  ls -lh build/linux-release/bin/game
  ```

## ✅ Verificación de Dependencias

- [ ] Ver qué depende de qué:
  ```bash
  cd /home/ismael/Game/rtaiz/build/linux-debug/bin
  ldd ./game
  ```

- [ ] Debe mostrar las librerías de phobos:
  ```
  libphobos_graphics.so.1 =>
  libphobos_window.so.1 =>
  libphobos_sound.so.1 =>
  libphobos_io.so.1 =>
  libphobos_common.so.1 =>
  ```

## ✅ Verificación de IntelliSense

- [ ] Abrir [phobos/common/include/phobos/common/common.hpp](phobos/common/include/phobos/common/common.hpp)

- [ ] Verificar que se muestre autocompletado en VS Code

- [ ] Pasar mouse sobre símbolos para ver tipo

- [ ] Si no funciona, ejecutar:
  ```
  Ctrl+Shift+P → "C/C++: Rescan Solution"
  ```

## ✅ Limpieza

- [ ] Limpiar archivos de compilación:
  ```bash
  rm -rf build CMakeCache.txt
  ```

- [ ] Verificar que build/ no existe:
  ```bash
  ls -la | grep build
  ```

- [ ] Reconfigurar desde cero:
  ```bash
  cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
  cmake --build build/linux-debug
  ```

## ✅ Windows (si aplica)

- [ ] Abrir Command Prompt o PowerShell

- [ ] Navegar a la carpeta:
  ```cmd
  cd Rutatuya\rtaiz
  ```

- [ ] Ejecutar script:
  ```cmd
  build.bat debug
  ```

- [ ] Debe compilar exitosamente

- [ ] Ejecutar:
  ```cmd
  .\build\windows-debug\bin\Debug\game.exe
  ```

## ✅ Desarrollo - Agregar Nuevo Módulo

- [ ] Crear estructura `phobos/mymodule/`

- [ ] Crear [phobos/mymodule/CMakeLists.txt](phobos/mymodule/CMakeLists.txt) basado en `common`

- [ ] Agregar a [phobos/CMakeLists.txt](phobos/CMakeLists.txt):
  ```cmake
  add_subdirectory(mymodule)
  target_link_libraries(phobos INTERFACE phobos_mymodule)
  ```

- [ ] Reconfigurar:
  ```bash
  cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
  cmake --build build/linux-debug
  ```

- [ ] Módulo debe compilar sin errores

## ✅ Problema: Algo No Funciona

1. **CMake no configura**:
   ```bash
   rm -rf build CMakeCache.txt CMakeFiles
   cmake -B build/linux-debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -Wno-dev
   ```

2. **Errores de compilación**:
   ```bash
   cmake --build build/linux-debug --verbose
   ```

3. **Librerías no encontradas en tiempo de ejecución**:
   ```bash
   export LD_LIBRARY_PATH=/home/ismael/Game/rtaiz/build/linux-debug/lib:$LD_LIBRARY_PATH
   ./build/linux-debug/bin/game
   ```

4. **IntelliSense no funciona en VS Code**:
   - `Ctrl+Shift+P` → "C/C++: Reset IntelliSenseDatabase"
   - O: `Ctrl+Shift+P` → "CMake: Reconfigure"

5. **GDB no funciona**:
   ```bash
   which gdb
   ```
   Si no existe: `sudo apt install gdb`

## ✅ Éxito Final

Si todos los puntos están marcados, ¡el proyecto está listo para desarrollar!

**Próximos pasos**:
- [ ] Leer [CMAKE_GUIDE.md](CMAKE_GUIDE.md) para entender la estructura
- [ ] Leer [QUICK_START.md](QUICK_START.md) para tips rápidos
- [ ] Explorar el código en [phobos/](phobos/) y [game/game/src/main.cpp](game/src/main.cpp)
- [ ] Agregar nuevo módulo o dependencia externa
- [ ] ¡Crear tu juego!

---

**Versión**: 1.0
**Última actualización**: 25 de abril de 2026
**Plataformas probadas**: Linux x64 (Ubuntu 22.04+)
