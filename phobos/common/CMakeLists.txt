cmake_minimum_required(VERSION 3.22)
project(phobos_common CXX)

message(STATUS "  Configurando common...")

# Archivos fuente
set(COMMON_SOURCES
    src/common.cpp
    src/phobos_class.cpp
    src/logger.cpp
    src/object.cpp
    src/utils.cpp
)

file(GLOB COMMON_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Crear librería compartida
add_library(phobos_common SHARED
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

# Configurar includes
target_include_directories(phobos_common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_common PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${COMMON_HEADERS}"
)

# Exportar target
install(TARGETS phobos_common
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  common configurado")
