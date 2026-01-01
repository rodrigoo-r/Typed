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