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

#include "ADT/Exception/UnknownToken.h"
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
        if (state.IsStringLiteral() && c != '"')
        {
            state.AddColumn();
            continue;
        }

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

        else if (c == ';' || c == ' ')
        {
            Flush();
        }

        else if (c == '\n')
        {
            Flush();
            state.AddLine();

            continue;
        }

        else if (
            state.GetSize() == 1 &&
            (
                (c >= 'a' && c <= 'z') ||
                c == '_' ||
                c >= 'A' && c <= 'Z'
            )
        )
        {
            state.ToggleIdentifier();
        }

        else if (
            state.GetSize() == 1 &&
            c >= '0' && c <= '9'
        )
        {
            state.ToggleNumberLiteral();
        }

        else if (
            c == '.' &&
            state.IsNumberLiteral()
        )
        {
            // Prevent numbers like "1.12.2"
            if (state.IsFloatLiteral())
            {
                throw ADT::Exception::UnknwonToken(
                    state.GetLine(),
                    state.GetColumn()
                );
            }

            state.ToggleFloatLiteral();
        }

        state.AddColumn();
    }
}
