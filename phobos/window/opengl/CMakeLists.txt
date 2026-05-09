cmake_minimum_required(VERSION 3.22)
project(phobos_window_opengl CXX)

message(STATUS "  Configurando window/opengl...")

# Dependencias
find_package(OpenGL REQUIRED)

# Archivos fuente
set(OPENGL_SOURCES
    src/opengl.cpp
)

set(OPENGL_HEADERS
    include/phobos/window/opengl/opengl.hpp
)

# Crear librería compartida
add_library(phobos_window_opengl SHARED
    ${OPENGL_SOURCES}
    ${OPENGL_HEADERS}
)

# Dependencias
target_link_libraries(phobos_window_opengl
    PUBLIC phobos_window
    PUBLIC OpenGL::GL
)

# Configurar includes
target_include_directories(phobos_window_opengl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_window_opengl PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${OPENGL_HEADERS}"
)

# Exportar target
install(TARGETS phobos_window_opengl
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)