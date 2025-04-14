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
add_game_library(Updatable INTERFACE)

add_library(GameState INTERFACE)
target_include_directories(GameState INTERFACE Updatable ${CMAKE_SOURCE_DIR}/include)

add_library(Component INTERFACE)
target_include_directories(Component INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(utils INTERFACE)
target_include_directories(utils INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(Grid INTERFACE)
target_include_directories(Grid INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(Clickable INTERFACE)
target_include_directories(Clickable INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(Cell STATIC src/Cell.cpp)
target_include_directories(Cell PUBLIC include)

add_library(ResourceManager STATIC src/ResourceManager.cpp)
target_include_directories(ResourceManager PUBLIC include)
target_link_libraries(ResourceManager PUBLIC ${SFML_DEPENDENCIES})

add_library(Button STATIC src/Button.cpp)
target_include_directories(Button PUBLIC include)
target_link_libraries(Button PUBLIC Component ResourceManager Clickable ${SFML_DEPENDENCIES})

add_library(Counter STATIC src/Counter.cpp)
target_include_directories(Counter PUBLIC include)
target_link_libraries(Counter PUBLIC Component ResourceManager ${SFML_DEPENDENCIES})

add_library(StopWatch STATIC src/StopWatch.cpp)
target_include_directories(StopWatch PUBLIC include)
target_link_libraries(StopWatch PUBLIC Counter Updatable)

add_library(FlagCounter STATIC src/FlagCounter.cpp)
target_include_directories(FlagCounter PUBLIC include)
target_link_libraries(FlagCounter PUBLIC Counter Updatable GameCore)

add_library(Board STATIC src/Board.cpp)
target_include_directories(Board PUBLIC include)
target_link_libraries(Board PUBLIC GameData Cell utils Grid ${SFML_DEPENDENCIES})

add_library(GameLogic STATIC src/GameLogic.cpp)
target_include_directories(GameLogic PUBLIC include)
target_link_libraries(GameLogic PUBLIC GameData Cell Board utils ${SFML_DEPENDENCIES})

add_library(GameCore STATIC src/GameCore.cpp)
target_include_directories(GameCore PUBLIC include)
target_link_libraries(GameCore PUBLIC GameData Cell ResourceManager Component Board Clickable GameLogic utils ${SFML_DEPENDENCIES})

add_library(Container STATIC src/Container.cpp)
target_include_directories(Container PUBLIC include)
target_link_libraries(Container PUBLIC Component Clickable Updatable ${SFML_DEPENDENCIES})

add_library(MainState STATIC src/state/MainState.cpp)
target_include_directories(MainState PUBLIC include/state)
target_link_libraries(MainState PUBLIC GameData GameState ResourceManager GameCore Container Button StopWatch FlagCounter ${SFML_DEPENDENCIES})

add_library(MenuState STATIC src/state/MenuState.cpp)
target_include_directories(MenuState PUBLIC include/state)
target_link_libraries(MenuState PUBLIC GameData MainState GameState ResourceManager Button GameStateManager ${SFML_DEPENDENCIES})

add_library(GameStateManager STATIC src/state/GameStateManager.cpp)
target_include_directories(GameStateManager PUBLIC include/state)
target_link_libraries(GameStateManager PUBLIC GameState)

add_library(Game STATIC src/Game.cpp)
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC GameData MainState MenuState ResourceManager GameStateManager ${SFML_DEPENDENCIES})

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE src)
target_link_libraries(main PRIVATE Game)

install(TARGETS main DESTINATION bin)