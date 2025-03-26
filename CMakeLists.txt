cmake_minimum_required(VERSION 3.28)
project(mineswapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SFML_DEPENDENCIES SFML::Graphics SFML::Window SFML::System)

function(add_game_library name type)
  if(type STREQUAL "INTERFACE")
    add_library(${name} ${type})
    target_include_directories(${name} INTERFACE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${name} INTERFACE ${SFML_DEPENDENCIES})
  else()
    add_library(${name} ${type} src/${name}.cpp)
    target_include_directories(${name} PUBLIC ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${name} ${SFML_DEPENDENCIES})
  endif()
endfunction()

add_game_library(GameData INTERFACE)

add_library(Cell STATIC src/Cell.cpp)
target_include_directories(Cell PUBLIC include)

add_library(Board STATIC src/Board.cpp)
target_include_directories(Board PUBLIC include)
target_link_libraries(Board PUBLIC GameData Cell ${SFML_DEPENDENCIES})

add_library(Game STATIC src/Game.cpp)
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC GameData Board ${SFML_DEPENDENCIES})

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE src)
target_link_libraries(main PRIVATE Game)

install(TARGETS main DESTINATION bin)