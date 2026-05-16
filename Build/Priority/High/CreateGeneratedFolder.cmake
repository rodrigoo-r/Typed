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

# Add a generated folder inside the build directory,
# which can be used to store generated files during the
# build process
set(GENERATED_DIR "${CMAKE_BINARY_DIR}/Generated")

if (NOT EXISTS "${GENERATED_DIR}")
    file(MAKE_DIRECTORY "${GENERATED_DIR}")
else ()
    if (NOT IS_DIRECTORY "${GENERATED_DIR}")
        message(
                WARNING
                "A file with the same name as the generated directory already exists: ${GENERATED_DIR}"
                "This file will be deleted and replaced with a directory."
                "If you want to keep this file, please rename it or move it to another location."
        )

        file(REMOVE "${GENERATED_DIR}")
        file(MAKE_DIRECTORY "${GENERATED_DIR}")
    endif ()
endif()