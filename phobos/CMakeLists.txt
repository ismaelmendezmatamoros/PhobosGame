cmake_minimum_required(VERSION 3.22)
project(phobos CXX)

message(STATUS "=== Configurando phobos ===")

# Subproyectos de phobos
add_subdirectory(common)
add_subdirectory(window)
add_subdirectory(sound)
add_subdirectory(io)
add_subdirectory(graphics)
add_subdirectory(engine)

# Crear una librería de interfaz que agrupa todas las dependencias
add_library(phobos INTERFACE)

# Agregar todos los subproyectos como dependencias
target_link_libraries(phobos INTERFACE
    phobos_common
    phobos_window
    phobos_sound
    phobos_io
    phobos_graphics
)

# Exportar información para consumidores
target_include_directories(phobos INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/window/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sound/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/io/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/graphics/include>
)

# Instalar archivos
install(TARGETS phobos
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

message(STATUS "phobos configurado exitosamente")
