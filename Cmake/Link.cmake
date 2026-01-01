# ============================================================================ #
# Executable & Libraries
# ============================================================================ #

if (APPLE) # macOS links xxhash statically, so no need to link it again
    target_link_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/opt/xxhash/lib)
endif ()

# Link libraries
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        Celery::Celery
        unordered_dense::unordered_dense
        xxhash
        magic_enum::magic_enum
)