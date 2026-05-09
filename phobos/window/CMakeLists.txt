cmake_minimum_required(VERSION 3.22)
project(phobos_window CXX)

message(STATUS "  Configurando window...")

add_subdirectory(opengl)

# Dependencias
include(FetchContent)

# TODO: Configurar aquí dependencias externas si se necesitan
# Ejemplo: FetchContent_Declare(glfw3 ...)
# FetchContent_MakeAvailable(glfw3)

# Archivos fuente
set(WINDOW_SOURCES
    src/window.cpp
)

set(WINDOW_HEADERS
    include/phobos/window/window.hpp
)

# Crear librería compartida
add_library(phobos_window SHARED
    ${WINDOW_SOURCES}
    ${WINDOW_HEADERS}
)

# Dependencias
target_link_libraries(phobos_window
    PUBLIC phobos_common
)

# Configurar includes
target_include_directories(phobos_window
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_window PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${WINDOW_HEADERS}"
)

# Exportar target
install(TARGETS phobos_window
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/phobos/window
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  window configurado")
