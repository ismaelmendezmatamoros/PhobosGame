cmake_minimum_required(VERSION 3.22)
project(rtaiz CXX)

# Configuración global
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configurar output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Activar testing
enable_testing()

# Opciones de compilación
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# FetchContent para gestionar dependencias externas
include(FetchContent)

# Avisos de configuración
message(STATUS "=== Configuración de rtaiz ===")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Plataforma: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")

# Subproyectos
add_subdirectory(phobos)
add_subdirectory(game)
