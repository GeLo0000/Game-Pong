cmake_minimum_required(VERSION 3.10)

project(Game-Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)

add_executable(Game-Pong main.cpp)

target_link_libraries(Game-Pong PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    add_custom_command(TARGET Game-Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:Game-Pong>
    )
endif()