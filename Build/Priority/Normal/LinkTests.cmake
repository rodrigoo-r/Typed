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

target_link_libraries(
        ${TEST_TARGET_NAME}
        PRIVATE
        ${PROJECT_NAME}
        GTest::gtest
        GTest::gtest_main
)

enable_testing()
add_test(NAME Typed_Tests COMMAND Typed_Tests)