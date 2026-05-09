cmake_minimum_required(VERSION 3.22)
project(phobos_window_vulkan CXX)

message(STATUS "    Configurando window_vulkan...")

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

if(NOT DEFINED GLFW_TARGET OR NOT DEFINED VULKAN_TARGET)
    include(FetchContent)
endif()

if(NOT DEFINED GLFW_TARGET)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.10
    )
    FetchContent_MakeAvailable(glfw)
    set(GLFW_TARGET glfw)
endif()

if(NOT DEFINED VULKAN_TARGET)
    FetchContent_Declare(VulkanHeaders
        URL https://github.com/KhronosGroup/Vulkan-Headers/archive/refs/tags/v1.3.261.tar.gz
    )

    FetchContent_Declare(VulkanLoader
        URL https://github.com/KhronosGroup/Vulkan-Loader/archive/refs/tags/v1.3.261.tar.gz
    )

    FetchContent_MakeAvailable(VulkanHeaders VulkanLoader)
    set(VULKAN_TARGET Vulkan::Vulkan)
endif()

set(VULKAN_SOURCES
    src/vulkan.cpp
)

set(VULKAN_HEADERS
    include/vulkan.hpp
)

add_library(phobos_window_vulkan SHARED
    ${VULKAN_SOURCES}
    ${VULKAN_HEADERS}
)

target_compile_definitions(phobos_window_vulkan PUBLIC USE_WINDOW_VULKAN)

target_link_libraries(phobos_window_vulkan
    PUBLIC ${GLFW_TARGET}
    PUBLIC ${VULKAN_TARGET}
)

if(X11_FOUND)
    target_include_directories(phobos_window_vulkan PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(phobos_window_vulkan PUBLIC ${X11_LIBRARIES})
endif()

target_include_directories(phobos_window_vulkan
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(phobos_window_vulkan PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${VULKAN_HEADERS}"
)

install(TARGETS phobos_window_vulkan
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

message(STATUS "    window_vulkan configurado")
