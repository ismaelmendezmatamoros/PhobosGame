cmake_minimum_required(VERSION 3.22)
project(game CXX)

message(STATUS "=== Configurando game ===")

# Archivos fuente del ejecutable
set(GAME_SOURCES
    src/main.cpp
)

# Crear ejecutable
add_executable(game ${GAME_SOURCES})

# Dependencias
target_link_libraries(game
    PRIVATE 
    engine
)

# Configurar includes
target_include_directories(game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Propiedades del ejecutable
set_target_properties(game PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

# Instalar ejecutable
install(TARGETS game
    RUNTIME DESTINATION bin
)

message(STATUS "game configurado exitosamente")
