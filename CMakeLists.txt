cmake_minimum_required(VERSION 3.10)

project(Game-Pong)

# === C++ Standard ===
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === SFML Configuration ===
include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)

# === Source Files ===
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/input_handler.cpp
    src/window.cpp
)

set(HEADERS
    include/game.h
    include/input_handler.h
    include/window.h
)

# === Create Executable ===
add_executable(Game-Pong ${SOURCES})

# === Include Directories ===
target_include_directories(Game-Pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# === Link Libraries ===
target_link_libraries(Game-Pong PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
    sfml-audio
)

# === Copy Assets to Build Directory ===
add_custom_command(TARGET Game-Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Game-Pong>/assets
    COMMENT "Copying assets to build directory"
)

# === Windows: Copy DLLs ===
if(WIN32)
    add_custom_command(TARGET Game-Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:Game-Pong>
        COMMENT "Copying SFML DLLs"
    )
endif()

# === Linux/macOS: Set RPATH for Shared Libraries ===
if(UNIX AND NOT APPLE)
    set_target_properties(Game-Pong PROPERTIES
        BUILD_RPATH "$ORIGIN/../lib:$ORIGIN/../external/lib"
        INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/../external/lib"
    )
endif()

# === Install Target ===
install(TARGETS Game-Pong RUNTIME DESTINATION .)
install(DIRECTORY assets DESTINATION .)

if(WIN32)
    install(
        FILES
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        DESTINATION .
    )
endif()