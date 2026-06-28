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
    src/timming.cpp
    src/game_fsm.cpp
)

file(GLOB COMMON_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# GLM es requerido porque window_base_interface.hpp incluye cabeceras de glm
find_package(glm 0.9.9 QUIET)
if(NOT TARGET glm::glm)
    include(FetchContent)
    FetchContent_Declare(glm
        URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
    )
    FetchContent_MakeAvailable(glm)
endif()

# Crear librería compartida
add_library(phobos_common SHARED
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

# Configurar includes
target_include_directories(phobos_common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../io/io_common/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../window/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../engine/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(phobos_common
    PUBLIC
        glm::glm
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
