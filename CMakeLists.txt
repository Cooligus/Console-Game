###########################################################
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non - commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain.We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors.We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to < http://unlicense.org/ >
###########################################################

# Set cmake minimum version
cmake_minimum_required (VERSION 3.0)

# Set up project
project (Console-Game VERSION 1.5.1)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Set project executable
add_executable (Console-Game
    "${SRC_DIR}/board.cpp"
    "${SRC_DIR}/direction.cpp"
    "${SRC_DIR}/game.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/positioned.cpp"
    "${SRC_DIR}/config.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rc/icon.rc"
        )


# Define list with names of config variables for game
list(APPEND GAME_NAMES
    "CONFIG_CG"
    "SIZE_X"
    "SIZE_Y"
    "PLAYER_POSITION_X"
    "PLAYER_POSITION_Y"
    "ENEMIES_AMOUNT"
    "ADD_FRAMES"
    "REPLACE_SPACE"
    "SPACE_CHAR"
    "FRAME_CHAR"
    "PLAYER_SPRITE"
    "POINT_SPRITE"
    "ENEMY_SPRITE"
    )

# Define list with names of variables in config
list(APPEND CG_NAMES
    "ConfigCG"
    "sizeX"
    "sizeY"
    "playerPositionX"
    "playerPositionY"
    "enemiesAmount"
    "addFrames"
    "replaceSpaceByFrame"
    "spaceChar"
    "frameChar"
    "playerSprite"
    "pointSprite"
    "enemySprite"
    )

# Set variables
set(INCREMENTER 0)
set(DEF "_DEF")
add_definitions(-DDEFAULT_PREPOSITION="${DEF}")

# Define foreach
foreach(VAR_NAME ${GAME_NAMES})
    
    # Get current name
    list(GET CG_NAMES ${INCREMENTER} CG_VAR_NAME)
    
    # Define VAR_NAME
    add_definitions(-D${VAR_NAME}="${CG_VAR_NAME}")

    # Set current variable to parrent scope
    set(${VAR_NAME} ${CG_VAR_NAME})

    # Increment incrementer
    math(EXPR INCREMENTER "${INCREMENTER}+1")

endforeach()

# Configure file with default definitions
configure_file("src/definitions.in.h" "src/definitions.h")
include_directories(${PROJECT_BINARY_DIR})

find_package(nlohmann_json REQUIRED)
include_directories(${NLOHMANN_INCLUDE_DIR})
target_link_libraries(Console-Game ${NLOHMANN_LIBRARIES})

# Set up pdcurses if it's windows
if(WIN32 OR MSVC)

    # Add special definition to have wide characters
    add_definitions(-DPDC_WIDE)
    
else()

    set(CURSES_NEED_NCURSES TRUE)
    set(CURSES_NEED_WIDE TRUE)

    #Find and include curses
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(Console-Game ${CURSES_LIBRARIES})

endif()

# Install project stuffs
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS ${PROJECT_NAME}
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)
