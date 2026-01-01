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

FetchContent_MakeAvailable(unordered_dense Celery)