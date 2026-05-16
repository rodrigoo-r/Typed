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

file(
        READ
        "${Black_Magic_Dir}/Template/Generated.h"
        Generated_Template_Content
)

function(GetGeneratedFileTemplate Out_Var)
    set(
            ${Out_Var}
            "${Generated_Template_Content}"
            PARENT_SCOPE
    )
endfunction()