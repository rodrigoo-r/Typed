# ============================================================================ #
# Executable & Libraries
# ============================================================================ #
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        Core
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Celery::Celery
        unordered_dense::unordered_dense
)