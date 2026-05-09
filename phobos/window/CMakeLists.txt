cmake_minimum_required(VERSION 3.22)
project(phobos_window CXX)

message(STATUS "  Configurando window...")

option(USE_WINDOW_OPENGL "Enable OpenGL support in window module" ON)
option(USE_WINDOW_VULKAN "Enable Vulkan support in window module" OFF)

if(USE_WINDOW_OPENGL AND USE_WINDOW_VULKAN)
    message(FATAL_ERROR "USE_WINDOW_OPENGL and USE_WINDOW_VULKAN cannot both be enabled at the same time.")
endif()

if(USE_WINDOW_VULKAN)
    add_subdirectory(window_vulkan)
elseif(USE_WINDOW_OPENGL)
    add_subdirectory(window_opengl)
else()
    message(STATUS "  No window backend selected; utilizando OpenGL por defecto.")
    add_subdirectory(window_opengl)
endif()

# Archivos fuente e incluye de la librería de interfaz
set(WINDOW_SOURCES
    src/window.cpp
)

set(WINDOW_HEADERS
    include/phobos/window/window.hpp
    include/phobos/window/window_base_interface.hpp
    include/phobos/window/windows_definitions.hpp
)

add_library(phobos_window SHARED
    ${WINDOW_SOURCES}
    ${WINDOW_HEADERS}
)

target_link_libraries(phobos_window
    PUBLIC phobos_common
)

if(TARGET phobos_window_opengl)
    target_link_libraries(phobos_window PUBLIC phobos_window_opengl)
endif()

if(TARGET phobos_window_vulkan)
    target_link_libraries(phobos_window PUBLIC phobos_window_vulkan)
endif()

# El proyecto window debe poder acceder a los headers del resto de phobos
target_include_directories(phobos_window
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../common/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../sound/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../io/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../graphics/include>
)

set_target_properties(phobos_window PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${WINDOW_HEADERS}"
)

install(TARGETS phobos_window
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/phobos/window
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  window configurado")
