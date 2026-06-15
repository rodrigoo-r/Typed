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

set(TEST_TARGET_NAME "${PROJECT_NAME}_Tests")
set(APP_TARGET_NAME "${PROJECT_NAME}_App")

# Define the abs path for the source directory
set(Src_Abs_Path "${CMAKE_SOURCE_DIR}/Src")
set(Test_Abs_Path "${CMAKE_SOURCE_DIR}/Test")
set(App_Abs_Path "${CMAKE_SOURCE_DIR}/App")

# Add all the source files to the project
file(GLOB_RECURSE Src_Files "${Src_Abs_Path}/*.cpp")
file(GLOB_RECURSE Header_Files "${Src_Abs_Path}/*.h")
file(GLOB_RECURSE App_Src_Files "${App_Abs_Path}/*.cpp")
file(GLOB_RECURSE Test_Src_Files "${Test_Abs_Path}/*.cpp")

add_library(${PROJECT_NAME} ${Src_Files} ${Header_Files})
target_include_directories(${PROJECT_NAME} PUBLIC include)
add_executable(${APP_TARGET_NAME} ${App_Src_Files})
add_executable(${TEST_TARGET_NAME} ${Test_Src_Files})

set_target_properties(${APP_TARGET_NAME} PROPERTIES OUTPUT_NAME "typed")