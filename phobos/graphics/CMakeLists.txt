cmake_minimum_required(VERSION 3.22)
project(phobos_graphics CXX)

message(STATUS "  Configurando graphics...")

option(USE_GRAPHICS_OPENGL "Enable OpenGL support in graphics module" ON)

# Dependencias
include(FetchContent)

# Descargar GLM - Librería de matemáticas para gráficos
FetchContent_Declare(glm
    URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
)

FetchContent_MakeAvailable(glm)

add_subdirectory(graphics_common)

if(USE_GRAPHICS_OPENGL)
    add_subdirectory(graphics_opengl)
else()
    message(STATUS "  USE_GRAPHICS_OPENGL está deshabilitado; no se compila graphics_opengl.")
endif()

set(GRAPHICS_SOURCES
    src/graphics.cpp
)

file(GLOB GRAPHICS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(phobos_graphics SHARED
    ${GRAPHICS_SOURCES}
    ${GRAPHICS_HEADERS}
)

target_link_libraries(phobos_graphics
    PUBLIC
        phobos_common
        phobos_window
        phobos_graphics_common
        glm::glm
)

if(TARGET phobos_graphics_opengl)
    target_link_libraries(phobos_graphics PUBLIC phobos_graphics_opengl)
endif()

target_include_directories(phobos_graphics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/graphics_common/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/graphics_opengl/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(phobos_graphics PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${GRAPHICS_HEADERS}"
)

install(TARGETS phobos_graphics
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  graphics configurado")
