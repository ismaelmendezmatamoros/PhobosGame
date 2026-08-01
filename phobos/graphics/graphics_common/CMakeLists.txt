cmake_minimum_required(VERSION 3.22)
project(phobos_graphics_common CXX)

message(STATUS "    Configurando graphics_common...")

set(GRAPHICS_COMMON_SOURCES
    src/graphics_base_interface.cpp
    src/shader_base_interface.cpp
    src/shader_stage_base_interface.cpp
    src/gpu_memory_manager_base_interface.cpp
    src/gpu_buffer_base_interface.cpp
    src/shader_manager.cpp
)

file(GLOB GRAPHICS_COMMON_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(phobos_graphics_common SHARED
    ${GRAPHICS_COMMON_SOURCES}
    ${GRAPHICS_COMMON_HEADERS}
)

target_link_libraries(phobos_graphics_common
    PUBLIC
        phobos_common
        phobos_window
        glm::glm
)

target_include_directories(phobos_graphics_common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(phobos_graphics_common PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${GRAPHICS_COMMON_HEADERS}"
)

install(TARGETS phobos_graphics_common
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "    graphics_common configurado")
