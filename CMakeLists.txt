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

set(SFML_DEPENDENCIES SFML::Graphics SFML::Window SFML::System SFML::Audio)

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
add_game_library(GameState INTERFACE)

add_library(Component INTERFACE)
target_include_directories(Component INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(Cell STATIC src/Cell.cpp)
target_include_directories(Cell PUBLIC include)

add_library(ResourceManager STATIC src/ResourceManager.cpp)
target_include_directories(ResourceManager PUBLIC include)
target_link_libraries(ResourceManager PUBLIC ${SFML_DEPENDENCIES})

add_library(Button STATIC src/Button.cpp)
target_include_directories(Button PUBLIC include)
target_link_libraries(Button PUBLIC Component ResourceManager ${SFML_DEPENDENCIES})

add_library(Panel STATIC src/Panel.cpp)
target_include_directories(Panel PUBLIC include)
target_link_libraries(Panel PUBLIC Button Component ResourceManager ${SFML_DEPENDENCIES})


add_library(Board STATIC src/Board.cpp)
target_include_directories(Board PUBLIC include)
target_link_libraries(Board PUBLIC GameData Cell ResourceManager Component ${SFML_DEPENDENCIES})

add_library(GameCore STATIC src/GameCore.cpp)
target_include_directories(GameCore PUBLIC include)
target_link_libraries(GameCore PUBLIC GameData Cell ResourceManager Component Board ${SFML_DEPENDENCIES})

add_library(MainState STATIC src/MainState.cpp)
target_include_directories(MainState PUBLIC include)
target_link_libraries(MainState PUBLIC GameData Cell Board GameState ResourceManager Panel GameCore ${SFML_DEPENDENCIES})

add_library(Game STATIC src/Game.cpp)
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC GameData MainState ResourceManager ${SFML_DEPENDENCIES})

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE src)
target_link_libraries(main PRIVATE Game)

install(TARGETS main DESTINATION bin)