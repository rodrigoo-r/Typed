# ============================================================================ #
# Include Directories
# ============================================================================ #
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        .
)

if (APPLE)
    target_include_directories(
            ${PROJECT_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/include
    )
endif ()