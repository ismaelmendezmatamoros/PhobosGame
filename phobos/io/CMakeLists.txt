cmake_minimum_required(VERSION 3.22)
project(phobos_io CXX)

message(STATUS "  Configurando io...")

# Opción para seleccionar la implementación de IO
# Por defecto, usar io_glfw
option(USE_IO_GLFW "Usar implementación GLFW para IO" ON)

# Subproyecto común - siempre se compila
message(STATUS "    Agregando subproyecto io_common...")
add_subdirectory(io_common)

# Subproyecto específico de GLFW - solo si está habilitado
if(USE_IO_GLFW)
    message(STATUS "    Agregando subproyecto io_glfw...")
    add_subdirectory(io_glfw)
else()
    message(WARNING "    IO no tiene implementación habilitada. USE_IO_GLFW está desactivado.")
endif()

# ==============================================================================
# Crear la librería phobos_io que expone la implementación seleccionada
# ==============================================================================

# Archivos fuente de la interfaz de IO
set(IO_SOURCES
    src/io.cpp
)

file(GLOB IO_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Crear librería compartida
add_library(phobos_io SHARED
    ${IO_SOURCES}
    ${IO_HEADERS}
)

# Dependencias según la implementación seleccionada
if(USE_IO_GLFW)
    # phobos_io depende de phobos_io_glfw
    # (que a su vez depende de phobos_io_common transitivamente)
    target_link_libraries(phobos_io
        PUBLIC phobos_io_glfw
        PUBLIC phobos_common
    )
    
    # Propagar la definición de compilación
    target_compile_definitions(phobos_io PUBLIC USE_IO_GLFW)
else()
    # Si no hay ninguna implementación, al menos depender de lo común
    target_link_libraries(phobos_io
        PUBLIC phobos_io_common
        PUBLIC phobos_common
    )
endif()

# Configurar includes
target_include_directories(phobos_io
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Propiedades de la librería
set_target_properties(phobos_io PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "${IO_HEADERS}"
)

# Exportar target
install(TARGETS phobos_io
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

message(STATUS "  io configurado exitosamente")

install(TARGETS phobos_io
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "  io configurado")
