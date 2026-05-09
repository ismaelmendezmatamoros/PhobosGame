cmake_minimum_required(VERSION 3.22)
project(phobos_graphics CXX)

message(STATUS "  Configurando graphics...")

# Dependencias
include(FetchContent)

# Descargar GLM - Librería de matemáticas para gráficos
FetchContent_Declare(glm
    URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
)

FetchContent_MakeAvailable(glm)

# TODO: Configurar aquí otras dependencias externas si se necesitan
# Ejemplo: FetchContent_Declare(opengl ...)
# Ejemplo: FetchContent_Declare(glew ...)

# Archivos fuente
set(GRAPHICS_SOURCES
    src/graphics.cpp
)

file(GLOB GRAPHICS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Crear librería compartida
add_library(phobos_graphics SHARED
    ${GRAPHICS_SOURCES}
    ${GRAPHICS_HEADERS}
)

# Dependencias
target_link_libraries(phobos_graphics
    PUBLIC 
        phobos_common
        phobos_window
        glm::glm
)

# Configurar includes
target_include_directories(phobos_graphics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_graphics PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${GRAPHICS_HEADERS}"
)

# Exportar target
install(TARGETS phobos_graphics
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  graphics configurado")
