#-----------------------------------------------------#
#                                                     #
#                           Typed                     #
#                   A text formatting DSL             #
#                                                     #
#-----------------------------------------------------#
#                                                     #
#         Created by Rodrigo R. & Contributors        #
#         Released under the Apache License 2.0       #
#            Check LICENSE.MD for more info           #
#                                                     #
#-----------------------------------------------------#

# Defines the path for the Build directory, which
# contains the CMake files for the project.
set(BUILD_ABS_PATH "${CMAKE_SOURCE_DIR}/Build")
set(BUILD_FILES_PRIORITY_PATH "${BUILD_ABS_PATH}/Priority")

# Now, we include the CMake files by priority
# In the order:
# - Highest
# - High
# - Normal
# - Low
# - Lowest
set(
    PRIORITY_FILES_ORDER
    "Highest"
    "High"
    "Normal"
    "Low"
    "Lowest"
)

# Loop through the priority files and include them
foreach (PRIORITY ${PRIORITY_FILES_ORDER})
    set(PRIORITY_PATH "${BUILD_FILES_PRIORITY_PATH}/${PRIORITY}")
    if (NOT EXISTS ${PRIORITY_PATH})
        message(
                WARNING
                "The priority directory ${PRIORITY_PATH} does not exist. Skipping."
        )
    else ()
        # Make sure the path is a directory
        if (NOT IS_DIRECTORY ${PRIORITY_PATH})
            message(
                    FATAL_ERROR
                    "The path ${PRIORITY_PATH} is not a directory."
            )
        endif ()

        # Loop through the CMake files in the priority directory and include them
        file(GLOB PRIORITY_FILES "${PRIORITY_PATH}/*.cmake")
        foreach (PRIORITY_FILE ${PRIORITY_FILES})
            include(${PRIORITY_FILE})
        endforeach ()
    endif ()
endforeach ()