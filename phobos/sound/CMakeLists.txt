cmake_minimum_required(VERSION 3.22)
project(phobos_sound CXX)

message(STATUS "  Configurando sound...")

# Dependencias
include(FetchContent)

# TODO: Configurar aquí dependencias externas si se necesitan
# Ejemplo: FetchContent_Declare(openal ...)
# FetchContent_MakeAvailable(openal)

# Archivos fuente
set(SOUND_SOURCES
    src/sound.cpp
)

set(SOUND_HEADERS
    include/phobos/sound/sound.hpp
)

# Crear librería compartida
add_library(phobos_sound SHARED
    ${SOUND_SOURCES}
    ${SOUND_HEADERS}
)

# Dependencias
target_link_libraries(phobos_sound
    PUBLIC phobos_common
)

# Configurar includes
target_include_directories(phobos_sound
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_sound PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${SOUND_HEADERS}"
)

# Exportar target
install(TARGETS phobos_sound
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/phobos/sound
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  sound configurado")
