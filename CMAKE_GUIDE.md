# Estructura de CMake - Documentación Técnica

## Visión General

El proyecto usa una estructura jerárquica de CMake donde cada módulo es una librería compartida (`.so` en Linux, `.dll` en Windows), excepto `game` que es un ejecutable.

```
CMakeLists.txt (raíz)
  └─ phobos/CMakeLists.txt (agrupa subproyectos)
     ├─ common/CMakeLists.txt (librería base)
     ├─ window/CMakeLists.txt (depende de: common)
     ├─ sound/CMakeLists.txt (depende de: common)
     ├─ io/CMakeLists.txt (depende de: common)
     └─ graphics/CMakeLists.txt (depende de: window, common, GLM)
  └─ game/CMakeLists.txt (ejecutable, depende de: todo phobos)
```

## Archivo Raíz: `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.22)
project(rtaiz CXX)

# C++23 forzado globalmente
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorios de output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Incluir todos los subproyectos
add_subdirectory(phobos)
add_subdirectory(game)
```

**Qué hace**:
- Define estándar C++ 23 para todo el proyecto
- Configura dónde irán los ejecutables y librerías
- Carga los subproyectos principales

## `phobos/CMakeLists.txt`

```cmake
# Carga todos los subproyectos
add_subdirectory(common)
add_subdirectory(window)
add_subdirectory(sound)
add_subdirectory(io)
add_subdirectory(graphics)

# Crea una interfaz que agrupa todo
add_library(phobos INTERFACE)

# Todos los subproyectos se vinculan aquí
target_link_libraries(phobos INTERFACE
    phobos_common
    phobos_window
    phobos_sound
    phobos_io
    phobos_graphics
)
```

**Qué hace**:
- Carga todos los módulos
- Crea "phobos" como agrupa lógica
- Quien dependa de "phobos" obtiene todas las librerías

## Módulos Individuales: `common/CMakeLists.txt`

```cmake
# Archivos fuente
set(COMMON_SOURCES
    src/common.cpp
)

# Archivos header
set(COMMON_HEADERS
    include/phobos/common/common.hpp
)

# Crear librería compartida
add_library(phobos_common SHARED
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

# Ruta de headers para usuarios de esta librería
target_include_directories(phobos_common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Propiedades de versión
set_target_properties(phobos_common PROPERTIES
    VERSION 1.0
    SOVERSION 1
)
```

**Qué hace**:
- Define qué archivos forman la librería
- Specify public headers (accesibles desde afuera)
- Configura versionado de librería

## Módulos con Dependencias: `graphics/CMakeLists.txt`

```cmake
# Descargar dependencia externa
FetchContent_Declare(glm
    URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
)
FetchContent_MakeAvailable(glm)

# Crear librería
add_library(phobos_graphics SHARED ...)

# Vincular dependencias
target_link_libraries(phobos_graphics
    PUBLIC 
        phobos_common      # Dependencia interna
        phobos_window      # Dependencia interna
        glm::glm           # Dependencia externa
)
```

**Qué hace**:
- Descarga GLM automáticamente (FetchContent)
- Enlaza con otras librerías del proyecto
- Propaga las dependencias (PUBLIC)

## `game/CMakeLists.txt` (Ejecutable)

```cmake
# Archivos del ejecutable
set(GAME_SOURCES
    src/main.cpp
)

# Crear ejecutable
add_executable(game ${GAME_SOURCES})

# Vincular contra el motor completo
target_link_libraries(game
    PRIVATE 
        phobos
        phobos_common
        phobos_window
        phobos_sound
        phobos_io
        phobos_graphics
)
```

**Qué hace**:
- Crea un ejecutable en lugar de librería
- Lo enlaza contra todos los módulos disponibles
- Usa PRIVATE (no propaga dependencias)

## Conceptos Clave

### `add_library()` vs `add_executable()`

```cmake
# Librería (puede ser usada por otros)
add_library(mylib SHARED source.cpp)

# Ejecutable (programa final)
add_executable(myapp main.cpp)
```

### `target_link_libraries()`

Liga una librería con sus dependencias:

```cmake
# mylib depende de otherlib
target_link_libraries(mylib PRIVATE otherlib)

# Quién use mylib necesita otherlib también
target_link_libraries(mylib PUBLIC otherlib)

# Dependencia solo interna
target_link_libraries(mylib PRIVATE otherlib)
```

|Scope|Significado|
|-|-|
|PUBLIC|Visible para usuarios de esta librería|
|PRIVATE|Solo usa internamente|
|INTERFACE|Visible para usuarios pero no usada internamente|

### `target_include_directories()`

Define dónde están los headers:

```cmake
target_include_directories(mylib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
```

- `BUILD_INTERFACE`: Mientras se está compilando
- `INSTALL_INTERFACE`: Después de instalar
- `${CMAKE_CURRENT_SOURCE_DIR}`: Directorio del CMakeLists.txt

### `FetchContent`

Descarga dependencias automáticamente:

```cmake
include(FetchContent)

FetchContent_Declare(glm
    URL https://...
)

# Después se puede usar como:
target_link_libraries(mylib PUBLIC glm::glm)
```

## Tipos de Librerías

|Tipo|Extensión|Uso|
|-|-|-|
|Compartida (SHARED)|.so / .dll|Compartida ent programas|
|Estática (STATIC)|.a / .lib|Incluida en ejecutable|
|Header-only (INTERFACE)|-.hpp|Solo headers|

En este proyecto usamos **SHARED** para flexibilidad.

## Flujo de Compilación

1. **Configuración (CMake)**:
   ```
   cmake -B build/linux-debug ...
   ```
   - Lee todos los CMakeLists.txt
   - Valida dependencias
   - Descarga GLM
   - Genera Makefiles

2. **Compilación (Make/Ninja)**:
   ```
   cmake --build build/linux-debug
   ```
   - Compila phobos_common primero
   - Luego window (que depende de common)
   - Luego sound, io
   - Luego graphics (espera a window)
   - Finalmente game

3. **Resultado**:
   ```
   build/linux-debug/
   ├── bin/
   │   └── game          # Ejecutable
   └── lib/
       ├── libphobos_common.so
       ├── libphobos_window.so
       ├── libphobos_sound.so
       ├── libphobos_io.so
       ├── libphobos_graphics.so
       └── libglm_shared.so
   ```

## Agregar Nuevo Módulo

Ejemplo: `phobos/network/`

1. **Crear estructura**:
   ```
   phobos/network/
   ├── CMakeLists.txt
   ├── include/phobos/network/
   │   └── network.hpp
   └── src/
       └── network.cpp
   ```

2. **`phobos/network/CMakeLists.txt`**:
   ```cmake
   add_library(phobos_network SHARED
       src/network.cpp
       include/phobos/network/network.hpp
   )

   target_include_directories(phobos_network
       PUBLIC
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   )

   target_link_libraries(phobos_network PUBLIC phobos_common)
   ```

3. **Actualizar `phobos/CMakeLists.txt`**:
   ```cmake
   add_subdirectory(network)

   target_link_libraries(phobos INTERFACE phobos_network)
   ```

## Agregar Dependencia Externa

Ejemplo: Agregar GLFW a window

En `phobos/window/CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(glfw
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
)
FetchContent_MakeAvailable(glfw)

target_link_libraries(phobos_window PUBLIC glfw)
```

O con Git:

```cmake
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)
```

## Presets de CMake

`CMakePresets.json` define configuraciones estándar:

```json
{
    "configurePresets": [
        {
            "name": "linux-debug-build",
            "generator": "Unix Makefiles",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        }
    ]
}
```

Uso:
```bash
cmake --preset linux-debug-build --build-dir build
```

## Debugging de CMake

Ver qué se está haciendo:

```bash
cmake --debug-output -B build/linux-debug
cmake -B build/linux-debug --trace-expand 2>&1 | grep "glm"
```

Ver qué targets existen:

```bash
cmake -B build && cmake --build build --target help
```

## Variables Útiles

|Variable|Significado|
|-|-|
|`CMAKE_CXX_COMPILER`|Compilador C++ (g++, clang++, cl.exe)|
|`CMAKE_BUILD_TYPE`|Debug o Release|
|`CMAKE_SOURCE_DIR`|Raíz del proyecto|
|`CMAKE_CURRENT_SOURCE_DIR`|Directorio actual CMakeLists.txt|
|`CMAKE_BINARY_DIR`|Directorio de compilación|
|`CMAKE_INSTALL_PREFIX`|Dónde instalar (/usr/local, etc)|

## Recursos

- [CMake Documentation](https://cmake.org/cmake/help/latest/)
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
