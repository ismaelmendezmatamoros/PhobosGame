cmake_minimum_required(VERSION 3.22)
project(phobos_io_glfw CXX)

message(STATUS "    Configurando io_glfw...")

# Buscar GLFW
find_package(glfw3 QUIET)

# Configuración específica para Linux
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
endif()

# Buscar o descargar GLFW
if(NOT glfw3_FOUND)
    message(STATUS "GLFW3 no encontrado; descargando...")
    include(FetchContent)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.10
    )
    FetchContent_MakeAvailable(glfw)
    set(GLFW_TARGET glfw)
else()
    # Resolver el target correcto de GLFW
    if(TARGET glfw)
        set(GLFW_TARGET glfw)
    elseif(TARGET glfw3)
        set(GLFW_TARGET glfw3)
    elseif(TARGET glfw3::glfw)
        set(GLFW_TARGET glfw3::glfw)
    elseif(TARGET glfw::glfw)
        set(GLFW_TARGET glfw::glfw)
    else()
        set(GLFW_TARGET glfw3::glfw)
    endif()
endif()

# Archivos fuente
set(IO_GLFW_SOURCES
    src/io_glfw.cpp
)

set(IO_GLFW_HEADERS
    include/io_glfw.hpp
)

# Crear librería compartida
add_library(phobos_io_glfw SHARED
    ${IO_GLFW_SOURCES}
    ${IO_GLFW_HEADERS}
)

# Definir macro de compilación
target_compile_definitions(phobos_io_glfw PUBLIC USE_IO_GLFW)

# Dependencias
target_link_libraries(phobos_io_glfw
    PUBLIC ${GLFW_TARGET}
    PUBLIC phobos_window
    PUBLIC phobos_common)

# Configurar includes
target_include_directories(phobos_io_glfw
    PUBLIC
        # Headers de io_glfw
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        # Headers de io (solo para compilar io_glfw)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_io_glfw PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${IO_GLFW_HEADERS}"
)

# Exportar target
install(TARGETS phobos_io_glfw
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)
