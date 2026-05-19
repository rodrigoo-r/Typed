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
// Created by Rodrigo on 5/18/26.
//

#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::Parse()
{
    while (tokens.HasNext())
    {
        auto &token = tokens.Next();

        switch (token.type)
        {
            case ADT::Lang::TokenType::Use:
            {
                Use();
                break;
            }

            default:
            {
                break;
            }
        }
    }

    return root;
}
