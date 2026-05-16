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

# Define the abs path for the source directory
set(SRC_ABS_PATH "${CMAKE_SOURCE_DIR}/Src")

# Add all the source files to the project
file(GLOB_RECURSE SRC_FILES "${SRC_ABS_PATH}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${SRC_ABS_PATH}/*.h")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})