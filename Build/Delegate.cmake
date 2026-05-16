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
set(Build_Abs_Path "${CMAKE_SOURCE_DIR}/Build")
set(Build_Files_Priority_Path "${Build_Abs_Path}/Priority")

# Now, we include the CMake files by priority
# In the order:
# - Highest
# - High
# - Normal
# - Low
# - Lowest
set(
    Priority_Files_Order
    "Highest"
    "High"
    "Normal"
    "Low"
    "Lowest"
)

# Loop through the priority files and include them
foreach (Priority ${Priority_Files_Order})
    set(Priority_Path "${Build_Files_Priority_Path}/${Priority}")
    if (NOT EXISTS ${Priority_Path})
        message(
                WARNING
                "The priority directory ${Priority_Path} does not exist. Skipping."
        )
    else ()
        # Make sure the path is a directory
        if (NOT IS_DIRECTORY ${Priority_Path})
            message(
                    FATAL_ERROR
                    "The path ${Priority_Path} is not a directory."
            )
        endif ()

        # Loop through the CMake files in the priority directory and include them
        file(GLOB Priority_Files "${Priority_Path}/*.cmake")
        foreach (Priority_File ${Priority_Files})
            include(${Priority_File})
        endforeach ()
    endif ()
endforeach ()