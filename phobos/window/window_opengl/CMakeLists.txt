cmake_minimum_required(VERSION 3.22)
project(phobos_window_opengl CXX)

message(STATUS "    Configurando window_opengl...")

find_package(glfw3 QUIET)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_program(APT_GET apt-get)
    find_program(SUDO sudo)

    function(install_apt_packages packages)
        if(NOT APT_GET)
            message(FATAL_ERROR "apt-get no encontrado; no se pueden instalar paquetes del sistema: ${packages}")
        endif()
        if(SUDO)
            set(_sudo_cmd ${SUDO})
        else()
            set(_sudo_cmd)
        endif()
        string(REPLACE " " ";" package_list "${packages}")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E env DEBIAN_FRONTEND=noninteractive ${_sudo_cmd} ${APT_GET} update
            RESULT_VARIABLE _apt_update_result
            OUTPUT_QUIET
            ERROR_QUIET
        )
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E env DEBIAN_FRONTEND=noninteractive ${_sudo_cmd} ${APT_GET} install -y ${package_list}
            RESULT_VARIABLE _apt_install_result
            OUTPUT_VARIABLE _apt_install_output
            ERROR_VARIABLE _apt_install_error
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
        )
        if(NOT _apt_install_result EQUAL 0)
            message(FATAL_ERROR "No se pudieron instalar los paquetes: ${packages}\n${_apt_install_output}\n${_apt_install_error}")
        endif()
    endfunction()

    find_package(X11 QUIET COMPONENTS Xrandr Xinerama Xcursor Xi)
    if(NOT X11_FOUND)
        message(STATUS "X11 no encontrado; instalando paquetes necesarios...")
        install_apt_packages("libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev")
        find_package(X11 REQUIRED COMPONENTS Xrandr Xinerama Xcursor Xi)
    endif()
endif()

if(TARGET glfw)
    set(GLFW_TARGET glfw)
elseif(TARGET glfw3)
    set(GLFW_TARGET glfw3)
elseif(TARGET glfw3::glfw)
    set(GLFW_TARGET glfw3::glfw)
elseif(TARGET glfw::glfw)
    set(GLFW_TARGET glfw::glfw)
endif()

if(NOT DEFINED GLFW_TARGET)
    include(FetchContent)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.10
    )
    FetchContent_MakeAvailable(glfw)
    set(GLFW_TARGET glfw)
endif()

find_package(OpenGL REQUIRED)

set(OPENGL_SOURCES
    src/window_opengl.cpp
)

set(OPENGL_HEADERS
    include/window_opengl.hpp
)

add_library(phobos_window_opengl SHARED
    ${OPENGL_SOURCES}
    ${OPENGL_HEADERS}
)

target_compile_definitions(phobos_window_opengl PUBLIC USE_WINDOW_OPENGL)

target_link_libraries(phobos_window_opengl
    PUBLIC ${GLFW_TARGET}
    PUBLIC phobos_common
    PUBLIC OpenGL::GL
)

if(X11_FOUND)
    target_include_directories(phobos_window_opengl PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(phobos_window_opengl PUBLIC ${X11_LIBRARIES})
endif()

# Configurar includes
target_include_directories(phobos_window_opengl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_window_opengl PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${OPENGL_HEADERS}"
)

# Exportar target
install(TARGETS phobos_window_opengl
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)