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
set(Src_Abs_Path "${CMAKE_SOURCE_DIR}/Src")

# Add all the source files to the project
file(GLOB_RECURSE Src_Files "${Src_Abs_Path}/*.cpp")
file(GLOB_RECURSE Header_Files "${Src_Abs_Path}/*.h")

add_executable(${PROJECT_NAME} ${Src_Files} ${Header_Files})