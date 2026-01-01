# ============================================================================ #
# Dependencies
# ============================================================================ #
include(FetchContent)

# External projects
FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense
        GIT_TAG        v4.8.1
)
FetchContent_Declare(
        Celery
        GIT_REPOSITORY https://github.com/rodrigoo-r/Celery.git
        GIT_TAG        master
)
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG v0.9.7
)

if(NOT APPLE)
    FetchContent_Declare(
            xxhash
            GIT_REPOSITORY https://github.com/Cyan4973/xxHash
            GIT_TAG        v0.8.3
    )

    FetchContent_MakeAvailable(xxhash)
endif()

FetchContent_MakeAvailable(unordered_dense Celery magic_enum)