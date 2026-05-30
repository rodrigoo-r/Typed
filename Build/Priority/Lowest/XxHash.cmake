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

if (APPLE AND UNIX)
    target_link_directories(
            ${PROJECT_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/lib
    )

    target_link_directories(
            ${TEST_TARGET_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/lib
    )

    target_link_directories(
            ${APP_TARGET_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/lib
    )

    target_include_directories(
            ${PROJECT_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/include
    )

    target_include_directories(
            ${TEST_TARGET_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/include
    )

    target_include_directories(
            ${APP_TARGET_NAME}
            PRIVATE
            /opt/homebrew/opt/xxhash/include
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE xxhash)
    target_link_libraries(${TEST_TARGET_NAME} PRIVATE xxhash)
    target_link_libraries(${APP_TARGET_NAME} PRIVATE xxhash)
else ()
    target_include_directories(
            xxhash
            PUBLIC
            ${xxhash_SOURCE_DIR}
    )

    add_library(
            xxhash
            STATIC
            ${xxhash_SOURCE_DIR}/xxhash.c
    )

    target_link_libraries(
            ${PROJECT_NAME}
            PRIVATE
            xxhash
    )

    target_link_libraries(
            ${TEST_TARGET_NAME}
            PRIVATE
            xxhash
    )

    target_link_libraries(
            ${APP_TARGET_NAME}
            PRIVATE
            xxhash
    )
endif ()