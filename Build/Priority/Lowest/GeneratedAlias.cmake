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

# Add an alias for the generated directory so the source
# code can include generated files without using relative paths
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${Generated_Dir_Root}/Include
)