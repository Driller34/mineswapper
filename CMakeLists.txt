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

add_library(Updatable INTERFACE)
target_include_directories(Updatable INTERFACE ${CMAKE_SOURCE_DIR}/include/engine)

add_library(GameSettings INTERFACE)
target_include_directories(GameSettings INTERFACE ${CMAKE_SOURCE_DIR}/include/mineswapper)

add_library(WindowService STATIC src/WindowService.cpp)
target_include_directories(WindowService PUBLIC include)
target_link_libraries(WindowService PUBLIC ${SFML_DEPENDENCIES})

add_library(GameState INTERFACE)
target_include_directories(GameState INTERFACE 
    ${CMAKE_SOURCE_DIR}/include/engine
    ${CMAKE_SOURCE_DIR}/include/state
    ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(GameState INTERFACE Updatable)

add_library(Component INTERFACE)
target_include_directories(Component INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(utils INTERFACE)
target_include_directories(utils INTERFACE ${CMAKE_SOURCE_DIR}/include/engine)

add_library(Grid INTERFACE)
target_include_directories(Grid INTERFACE ${CMAKE_SOURCE_DIR}/include/mineswapper)

add_library(Clickable INTERFACE)
target_include_directories(Clickable INTERFACE ${CMAKE_SOURCE_DIR}/include/engine)

add_library(Cell STATIC src/mineswapper/Cell.cpp)
target_include_directories(Cell PUBLIC include/mineswapper)

add_library(ResourceManager STATIC src/engine/ResourceManager.cpp)
target_include_directories(ResourceManager PUBLIC include/engine)
target_link_libraries(ResourceManager PUBLIC ${SFML_DEPENDENCIES})

add_library(Button STATIC src/gui/Button.cpp)
target_include_directories(Button PUBLIC include/gui)
target_link_libraries(Button PUBLIC Component ResourceManager Clickable ${SFML_DEPENDENCIES})

add_library(Counter STATIC src/gui/Counter.cpp)
target_include_directories(Counter PUBLIC include/gui)
target_link_libraries(Counter PUBLIC Component ResourceManager ${SFML_DEPENDENCIES})

add_library(StopWatch STATIC src/gui/StopWatch.cpp)
target_include_directories(StopWatch PUBLIC include/gui)
target_link_libraries(StopWatch PUBLIC Counter Updatable)

add_library(FlagCounter STATIC src/gui/FlagCounter.cpp)
target_include_directories(FlagCounter PUBLIC include/gui)
target_link_libraries(FlagCounter PUBLIC Counter Updatable GameCore)

add_library(Board STATIC src/mineswapper/Board.cpp)
target_include_directories(Board PUBLIC include/mineswapper)
target_link_libraries(Board PUBLIC Cell utils Grid GameSettings ${SFML_DEPENDENCIES})

add_library(GameLogic STATIC src/mineswapper/GameLogic.cpp)
target_include_directories(GameLogic PUBLIC include/mineswapper)
target_link_libraries(GameLogic PUBLIC Cell Board utils GameSettings ${SFML_DEPENDENCIES})

add_library(GameCore STATIC src/mineswapper/GameCore.cpp)
target_include_directories(GameCore PUBLIC include/mineswapper)
target_link_libraries(GameCore PUBLIC Cell ResourceManager Component Board Clickable GameLogic utils GameSettings ${SFML_DEPENDENCIES})

add_library(Container STATIC src/gui/Container.cpp)
target_include_directories(Container PUBLIC include/gui)
target_link_libraries(Container PUBLIC Component Clickable Updatable ${SFML_DEPENDENCIES})

add_library(MainState STATIC src/state/MainState.cpp)
target_include_directories(MainState PUBLIC include/state)
target_link_libraries(MainState PUBLIC GameState ResourceManager GameCore Container Button StopWatch FlagCounter GameSettings WindowService ${SFML_DEPENDENCIES})

add_library(MenuState STATIC src/state/MenuState.cpp)
target_include_directories(MenuState PUBLIC include/state)
target_link_libraries(MenuState PUBLIC MainState GameState ResourceManager Button GameStateManager GameSettings WindowService ${SFML_DEPENDENCIES})

add_library(GameStateManager STATIC src/state/GameStateManager.cpp)
target_include_directories(GameStateManager PUBLIC include/state)
target_link_libraries(GameStateManager PUBLIC GameState)

add_library(Game STATIC src/Game.cpp)
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC MainState MenuState ResourceManager GameStateManager WindowService ${SFML_DEPENDENCIES})

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE src)
target_link_libraries(main PRIVATE Game)

install(TARGETS main DESTINATION bin)
