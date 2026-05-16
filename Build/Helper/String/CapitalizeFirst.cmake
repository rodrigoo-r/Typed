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

function(Capitalize_First Input Output)
    string(SUBSTRING "${${Input}}" 0 1 First_Char)
    string(SUBSTRING "${${Input}}" 1 -1 Rest_Chars)
    string(TOUPPER "${First_Char}" First_Char_Upper)
    set(${Output} "${First_Char_Upper}${Rest_Chars}" PARENT_SCOPE)
endfunction()