/*
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #                           Typed                     # *
 * #                   A text formatting DSL             # *
 * #                                                     # *
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #         Created by Rodrigo R. & Contributors        # *
 * #         Released under the Apache License 2.0       # *
 * #            Check LICENSE.MD for more info           # *
 * #                                                     # *
 * #-----------------------------------------------------# *
*/

//
// Created by Rodrigo on 5/19/26.
//

#pragma once
#include "ADT/Lang/Token.h"

namespace Typed::Support::Equality
{
    struct TokenType
    {
        static bool Equals(
            ADT::Lang::Token &token,
            ADT::Lang::TokenType type
        )
        {
            return token.type == type;
        }
    };
}