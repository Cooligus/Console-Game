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

# Define list with names of variables in config
set(types "types")
set(variables "variables")
set(definitions "definitions")

set(boolean "bool")
set(int "int")
set(str "string")

list(APPEND CONF_TYPES
    ${str}
    ${int}
    ${int}
    ${int}
    ${boolean}
    ${boolean}
    ${str}
    ${str}
    ${str}
    ${str}
    ${str}
    )

list(APPEND CONF_NAMES
    "ConfigCG"
    "sizeX"
    "sizeY"
    "enemiesAmount"
    "addFrames"
    "replaceSpaceByFrame"
    "spaceChar"
    "frameChar"
    "playerSprite"
    "pointSprite"
    "enemySprite"
    )

list(APPEND CONF_DEFS
    "ConfigCG.json"
    "10"
    "10"
    "2"
    "true"
    "false"
    " "
    "#"
    "O"
    "$"
    "D"
    )

# Set variables
set(INCREMENTER 0)
set(CONFIGURE_LIST "" )
set(DEF_PREFIX "_DEF")

# Define foreach
foreach(VAR_NAME ${CONF_NAMES})

    # Get content from other lists 
    list(GET CONF_TYPES ${INCREMENTER} CONF_TYPE)
    list(GET CONF_DEFS ${INCREMENTER} CONF_DEF)

    # Setup type
    set(CONFIGURE_STEP "${types}.push_back(\"${CONF_TYPE}\");\n")
    list(APPEND CONFIGURE_LIST ${CONFIGURE_STEP})

    # Setup name
    set(CONFIGURE_STEP "${variables}.push_back(\"${VAR_NAME}\");\n")
    list(APPEND CONFIGURE_LIST ${CONFIGURE_STEP})

    # Setup default value
    set(CONFIGURE_STEP "${definitions}.push_back(\"${CONF_DEF}\");\n")
    list(APPEND CONFIGURE_LIST ${CONFIGURE_STEP})

    set(${VAR_NAME} ${VAR_NAME})
    set(${VAR_NAME}${DEF_PREFIX} ${CONF_DEF})

    # Increment incrementer
    math(EXPR INCREMENTER "${INCREMENTER}+1")

endforeach()

# Configure files
configure_file("${CMAKE_SOURCE_DIR}/rc/ConfigCG.in.json" "${CMAKE_BINARY_DIR}/rc/ConfigCG.json")
configure_file("${CMAKE_SOURCE_DIR}/src/config.in.cpp" "${CMAKE_BINARY_DIR}/src/config.cpp")
configure_file("${CMAKE_SOURCE_DIR}/src/game.in.cpp" "${CMAKE_BINARY_DIR}/src/game.cpp")
configure_file("${CMAKE_SOURCE_DIR}/src/game.in.h" "${CMAKE_BINARY_DIR}/src/game.h")