cmake_minimum_required(VERSION 3.22)
project(phobos_window CXX)

message(STATUS "  Configurando window...")

# Dependencias externas
option(PREFER_SYSTEM_GLM "Prefer system-installed glm when available" ON)

if(PREFER_SYSTEM_GLM)
    find_package(glm 0.9.9 QUIET)
    if(TARGET glm::glm)
        message(STATUS "  Using system-installed glm")
    endif()
else()
    find_package(glm QUIET)
endif()

if(NOT TARGET glm::glm)
    include(FetchContent)
    FetchContent_Declare(glm
        URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
    )
    # Populate so we can patch older glm CMakeLists that require CMake < 3.5
    FetchContent_Populate(glm)
    if(EXISTS "${glm_SOURCE_DIR}/CMakeLists.txt")
        file(READ "${glm_SOURCE_DIR}/CMakeLists.txt" _glm_cmake_contents)
        string(REPLACE "cmake_minimum_required(VERSION 3.2 FATAL_ERROR)"
                       "cmake_minimum_required(VERSION 3.5 FATAL_ERROR)"
                       _glm_cmake_contents "${_glm_cmake_contents}")
        string(REPLACE "cmake_policy(VERSION 3.2)"
                       "cmake_policy(VERSION 3.5)"
                       _glm_cmake_contents "${_glm_cmake_contents}")
        file(WRITE "${glm_SOURCE_DIR}/CMakeLists.txt" "${_glm_cmake_contents}")
    endif()
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

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
    include/window.hpp
    include/window_base_interface.hpp
    include/windows_definitions.hpp
)

add_library(phobos_window SHARED
    ${WINDOW_SOURCES}
    ${WINDOW_HEADERS}
)

target_link_libraries(phobos_window
    PUBLIC phobos_common
    glm::glm
)

if(USE_WINDOW_OPENGL)
    target_compile_definitions(phobos_window PUBLIC USE_WINDOW_OPENGL)
endif()

if(USE_WINDOW_VULKAN)
    target_compile_definitions(phobos_window PUBLIC USE_WINDOW_VULKAN)
endif()

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/window_opengl/include>
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
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  window configurado")
