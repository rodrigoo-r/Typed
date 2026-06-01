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
#include "ADT/Exception/UnterminatedString.h"
#include "Lexer.h"

using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Lexer;

Machine::StreamRef Machine::Lex()
{
    // Clear the token stream
    tokens.Clear();

    // Iterate over the contents
    while (contents.HasNext())
    {
        auto c = contents.Next();
        if (state.IsStringLiteral() && c != '"')
        {
            if (c == '\n')
            {
                throw ADT::Exception::UnterminatedString(
                    state.GetLine(),
                    state.GetColumn()
                );
            }

            state.AddColumn();
            state.AddSize();
            continue;
        }

        if (state.GetSize() == 0)
        {
            state.SetStart(contents.Pos() - 1);
            state.SetTokenPosition(
                state.GetLine(),
                state.GetColumn()
            );
        }

        if (c == '"')
        {
            if (state.IsEscape())
            {
                state.AddColumn();
                state.AddSize();
                state.ToggleEscape();

                continue;
            }

            if (state.IsStringLiteral())
            {
                Flush();
                state.AddColumn();
                state.ResetSize();
            } else
            {
                Flush();
                state.AddColumn();
                state.ToggleStringLiteral();
                state.ResetSize();
            }

            continue;
        }

        if (c == '\\' && state.IsStringLiteral())
        {
            state.ToggleEscape();
            continue;
        }

        if (c == '#')
        {
            Flush();
            Comment();
            continue;
        }

        // Parse '==', '>=', '<=', '!='
        if (
            (
                c == '=' ||
                c == '>' ||
                c == '<'
            ) &&
            contents.HasNext() &&
            contents.Peek() == '='
        )
        {
            Flush();

            state.SetStart(contents.Pos() - 1);
            state.SetTokenPosition(
                state.GetLine(),
                state.GetColumn()
            );

            state.AddSize();
            state.AddSize();

            Flush();
            state.AddColumn();
            state.AddColumn();
            contents.Next();

            continue;
        }

        if (
            c == ';' ||
            c == ',' ||
            c == '>' ||
            c == '<'
        )
        {
            Flush();

            state.SetStart(contents.Pos() - 1);
            state.SetTokenPosition(
                state.GetLine(),
                state.GetColumn()
            );

            state.AddSize();

            Flush();
            state.AddColumn();

            continue;
        }

        if (c == ' ')
        {
            Flush();
            state.AddColumn();
            state.Reset();
            continue;
        }

        if (c == '\n')
        {
            Flush();
            state.AddLine();
            continue;
        }

        if (
            state.GetSize() == 0 &&
            (
                std::isalpha(c) ||
                c == '_'
            )
        )
        {
            state.ToggleIdentifier();
        }

        else if (
            state.IsIdentifier() &&
            !std::isalnum(c) &&
            c != '_'
        )
        {
            throw ADT::Exception::UnknownToken(
                state.GetLine(),
                state.GetColumn()
            );
        }

        else if (
            state.GetSize() == 0 &&
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
                throw ADT::Exception::UnknownToken(
                    state.GetLine(),
                    state.GetColumn()
                );
            }

            state.ToggleFloatLiteral();
        }

        state.AddColumn();
        state.AddSize();
    }

    // Last token
    Flush();

    return tokens;
}
