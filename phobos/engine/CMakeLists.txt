cmake_minimum_required(VERSION 3.22)
project(phobos_engine CXX)

message(STATUS "    Configurando engine...")

set(ENGINE_SOURCES
    src/engine.cpp
)

file(GLOB ENGINE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(engine SHARED
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_link_libraries(engine
    PUBLIC
        phobos_common
        phobos_window
        phobos_sound
        phobos_io
        phobos_graphics
)

target_include_directories(engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(engine PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${ENGINE_HEADERS}"
)

install(TARGETS engine
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

message(STATUS "    engine configurado")
