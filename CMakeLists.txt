cmake_minimum_required(VERSION 4.1)
project(Typed)

set(CMAKE_SCRIPTS_DIR "${CMAKE_SOURCE_DIR}/Cmake")
set(CMAKE_CXX_STANDARD 20)

# Modular CMake Includes
include(${CMAKE_SCRIPTS_DIR}/Source.cmake)
include(${CMAKE_SCRIPTS_DIR}/Libs.cmake)
include(${CMAKE_SCRIPTS_DIR}/Link.cmake)
include(${CMAKE_SCRIPTS_DIR}/IncludeDirs.cmake)