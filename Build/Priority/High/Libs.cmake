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

include(FetchContent)

# Fetch CLI11
FetchContent_Declare(
        CLI11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG v2.6.2
)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense
        GIT_TAG        v4.8.1
)

FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG        v0.9.8
)

FetchContent_Declare(
        absl
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG 20260526.rc1
)

FetchContent_Declare(
        re2
        GIT_REPOSITORY https://github.com/google/re2.git
        GIT_TAG 2025-11-05
)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Fetch xxHash only if the platform is not Apple
# For some weird reason, xxHash does not compile on macOS, so it's
# better for macOS users to install it system-wide instead of using the bundled version
if (NOT APPLE)
    FetchContent_Declare(
            xxhash
            GIT_REPOSITORY https://github.com/Cyan4973/xxHash.git
            GIT_TAG        v0.8.3
    )

    FetchContent_MakeAvailable(xxhash)
endif ()

FetchContent_MakeAvailable(
        CLI11
        unordered_dense
        magic_enum
        absl
        re2
        googletest
)