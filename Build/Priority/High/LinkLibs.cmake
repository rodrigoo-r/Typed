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

# Link all libraries
target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        Celery::Celery
        CLI11::CLI11
        unordered_dense::unordered_dense
        magic_enum::magic_enum
        re2
)