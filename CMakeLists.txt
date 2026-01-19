cmake_minimum_required(VERSION 3.28)
project(Game-Pong LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Paddle.cpp
    src/Ball.cpp
    src/EventManager.cpp
    src/ScoreManager.cpp
    src/GameMode.cpp
    src/ResourceManager.cpp
    src/AudioManager.cpp
)

set(HEADERS
    include/Game.hpp
    include/IGameObject.hpp
    include/Paddle.hpp
    include/Ball.hpp
    include/EventManager.hpp
    include/IEventListener.hpp
    include/ScoreManager.hpp
    include/GameMode.hpp
    include/ResourceManager.hpp
    include/AudioManager.hpp
)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS ON CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SFML)

add_executable(Game-Pong ${SOURCES})

target_include_directories(Game-Pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(Game-Pong PRIVATE cxx_std_17)
target_link_libraries(Game-Pong PRIVATE 
    SFML::Graphics 
    SFML::Audio
    SFML::System
    SFML::Window
)

add_custom_command(TARGET Game-Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMENT "Copying assets to bin directory"
)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game-Pong)
endif()