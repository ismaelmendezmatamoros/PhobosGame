cmake_minimum_required(VERSION 3.22)
project(phobos_io_common CXX)

message(STATUS "    Configurando io_common...")

# Archivos fuente
set(IO_COMMON_SOURCES
    src/filesystem.cpp
    src/io_base_interface.cpp
    src/key_mapper_interface.cpp
)

file(GLOB IO_COMMON_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Crear librería compartida
add_library(phobos_io_common SHARED
    ${IO_COMMON_SOURCES}
    ${IO_COMMON_HEADERS}
)

# Dependencias
target_link_libraries(phobos_io_common
    PUBLIC phobos_common
    PUBLIC phobos_window
)

# Configurar includes
target_include_directories(phobos_io_common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_io_common PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${IO_COMMON_HEADERS}"
)

# Exportar target
install(TARGETS phobos_io_common
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

message(STATUS "    io_common configurado exitosamente")
