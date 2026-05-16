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
set(Generated_Dir_Root "${CMAKE_BINARY_DIR}/Generated")
set(Generated_Dir "${Generated_Dir_Root}/Include/Generated")

if (NOT EXISTS "${Generated_Dir}")
    file(MAKE_DIRECTORY "${Generated_Dir}")
else ()
    if (NOT IS_DIRECTORY "${Generated_Dir}")
        message(
                WARNING
                "A file with the same name as the generated directory already exists: ${GENERATED_DIR}"
                "This file will be deleted and replaced with a directory."
                "If you want to keep this file, please rename it or move it to another location."
        )

        file(REMOVE "${Generated_Dir}")
        file(MAKE_DIRECTORY "${Generated_Dir}")
    endif ()
endif()