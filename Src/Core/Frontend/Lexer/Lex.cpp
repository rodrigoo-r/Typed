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

#include "Lexer.h"

using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Lexer;

Machine::ConstStreamRef Machine::Lex()
{
    // Clear the tokens stream
    tokens.Clear();

    // Iterate over the contents
    while (contents.HasNext())
    {
        auto c = contents.Next();

        if (c == '"')
        {
            if (state.IsStringLiteral())
            {
                Flush();
            }

            state.ToggleStringLiteral();
        }

        else if (c == '#')
        {
            Flush();
            Comment();
        }
    }
}
