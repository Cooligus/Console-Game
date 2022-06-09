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
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/src")

# Set project executable
add_executable (Console-Game
    "${SRC_DIR}/board.cpp"
    "${SRC_DIR}/direction.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/positioned.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rc/icon.rc"
    )

set_property(TARGET Console-Game PROPERTY CXX_STANDARD 11)

include(cmake/Config.cmake)
target_include_directories(Console-Game PRIVATE "${BIN_DIR}")
target_include_directories(Console-Game PRIVATE "${SRC_DIR}")

# Add configured files
target_sources(Console-Game PRIVATE "${BIN_DIR}/game.cpp" "${BIN_DIR}/config.cpp")

# Find JSON
find_package(nlohmann_json)

# Setup and download JSON if not found
if(nlohmann_json_FOUND EQUAL 1)
    target_link_libraries(Console-Game PRIVATE nlohmann_json::nlohmann_json)
else()
    FILE(DOWNLOAD 
        "https://raw.githubusercontent.com/nlohmann/json/release/3.10.5/single_include/nlohmann/json.hpp"
        "${CMAKE_BINARY_DIR}/src/nlohmann/json.hpp"
    )
    add_library(nlohmann_json INTERFACE)
    target_include_directories(Console-Game INTERFACE "${BIN_DIR}")
    target_link_libraries(Console-Game PRIVATE nlohmann_json)
endif()


# Set ncurses
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

option(MINGW_NCURSES_PATH "Path to ncurses if it is compiled via MinGW")

#Find and include curses (MinGW is needed if you want to compile it on Windows)
if(NOT WIN32)
    find_package(Curses REQUIRED)
    target_link_libraries(Console-Game PRIVATE ${CURSES_LIBRARIES})
else()
    target_include_directories(Console-Game PRIVATE "${MINGW_NCURSES_PATH}")
endif()

# Install project stuffs
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS ${PROJECT_NAME}
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)
