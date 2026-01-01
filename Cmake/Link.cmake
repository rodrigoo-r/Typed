# ============================================================================ #
# Executable & Libraries
# ============================================================================ #

# Link libraries
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        Celery::Celery
        unordered_dense::unordered_dense
)

if (APPLE) # macOS links xxhash statically, so no need to link it again
    target_link_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/opt/xxhash/lib)
endif ()

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        xxhash
)