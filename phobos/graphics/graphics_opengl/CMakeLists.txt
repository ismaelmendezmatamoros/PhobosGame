cmake_minimum_required(VERSION 3.22)
project(phobos_graphics_opengl CXX)

message(STATUS "    Configurando graphics_opengl...")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


set(GRAPHICS_OPENGL_SOURCES
    src/graphics_opengl.cpp
)

file(GLOB GRAPHICS_OPENGL_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(phobos_graphics_opengl SHARED
    ${GRAPHICS_OPENGL_SOURCES}
    ${GRAPHICS_OPENGL_HEADERS}
)

target_compile_definitions(phobos_graphics_opengl PUBLIC USE_GRAPHICS_OPENGL)

target_link_libraries(phobos_graphics_opengl
    PUBLIC
        phobos_graphics_common
        phobos_window
        OpenGL::GL
        glfw
        GLEW::GLEW
        glm::glm
)

target_include_directories(phobos_graphics_opengl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../graphics_common/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../window/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(phobos_graphics_opengl PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${GRAPHICS_OPENGL_HEADERS}"
)

install(TARGETS phobos_graphics_opengl
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "    graphics_opengl configurado")
