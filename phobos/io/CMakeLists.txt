cmake_minimum_required(VERSION 3.22)
project(phobos_io CXX)

message(STATUS "  Configurando io...")

# Dependencias
include(FetchContent)

# TODO: Configurar aquí dependencias externas si se necesitan

# Archivos fuente
set(IO_SOURCES
    src/filesystem.cpp
)

file(GLOB IO_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Crear librería compartida
add_library(phobos_io SHARED
    ${IO_SOURCES}
    ${IO_HEADERS}
)

# Dependencias
target_link_libraries(phobos_io
    PUBLIC phobos_common
)

# Configurar includes
target_include_directories(phobos_io
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_io PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${IO_HEADERS}"
)

# Exportar target
install(TARGETS phobos_io
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  io configurado")
