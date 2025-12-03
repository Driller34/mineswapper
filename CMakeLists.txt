cmake_minimum_required(VERSION 3.30)
project(mineswapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

set(SFML_DEPENDENCIES SFML::Graphics SFML::Window SFML::System SFML::Audio)

add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS src/*.cpp)

add_library(game STATIC ${ALL_SRC})
target_include_directories(game PUBLIC include)
target_link_libraries(game PUBLIC ${SFML_DEPENDENCIES})

add_executable(mineswapper src/main.cpp)
target_link_libraries(mineswapper PRIVATE game)

if(WIN32)
    target_link_options(mineswapper PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
endif()

install(TARGETS mineswapper DESTINATION bin)
