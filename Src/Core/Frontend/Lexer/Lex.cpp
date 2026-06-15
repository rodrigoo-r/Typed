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

#include "ADT/Exception/UnexpectedToken.h"
#include "ADT/Exception/UnknownToken.h"
#include "ADT/Exception/UnterminatedString.h"
#include "Lexer.h"
#include "Support/Printer/ASTPrinter.h"

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

        if (
            c == '\\' &&
            (
                state.IsStringLiteral() ||
                state.IsMultiLineStringLiteral()
            )
        )
        {
            state.ToggleEscape();
            state.AddColumn();
            state.AddSize();
            continue;
        }

        if (state.IsEscape())
        {
            auto escape_type = state.GetEscapeType();
            auto allowed_digits = -1;
            if (
                escape_type == ADT::Lang::EscapeType::NoEscape &&
                state.GetEscapeSize() == 0
            )
            {
                if (c == 'x')
                {
                    state.SetEscapeType(ADT::Lang::EscapeType::Hex);
                }
                else if (c == 'u')
                {
                    state.SetEscapeType(ADT::Lang::EscapeType::LowerUnicode);
                }
                else if (c == 'U')
                {
                    state.SetEscapeType(ADT::Lang::EscapeType::UpperUnicode);
                }
                else
                {
                    allowed_digits = 2;
                    state.ToggleEscape();
                }
            }
            else if (escape_type == ADT::Lang::EscapeType::Hex)
            {
                state.AddEscapeSize();
                allowed_digits = 2;
            }
            else if (escape_type == ADT::Lang::EscapeType::LowerUnicode)
            {
                state.AddEscapeSize();
                allowed_digits = 4;
            }
            else if (escape_type == ADT::Lang::EscapeType::UpperUnicode)
            {
                state.AddEscapeSize();
                allowed_digits = 8;
            }

            if (state.GetEscapeSize() >= allowed_digits)
            {
                state.ToggleEscape();
                state.AddColumn();
                state.AddSize();
                continue;
            }

            // Normal escape sequence
            state.AddColumn();
            state.AddSize();
            continue;
        }

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

        if (state.IsMultiLineStringLiteral() && c != '`')
        {
            if (c == '\n')
            {
                state.AddLine();
                state.AddSize();

                continue;
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

        if (
            c == '"' || c == '`'
        )
        {
            if (
                (
                    c == '"' &&
                    state.IsStringLiteral()
                ) || (
                    c == '`' &&
                    state.IsMultiLineStringLiteral()
                )
            )
            {
                Flush();
                state.AddColumn();
                state.ResetSize();
            } else if (
                (
                    c == '"' &&
                    !state.IsStringLiteral()
                ) || (
                    c == '`' &&
                    !state.IsMultiLineStringLiteral()
                )
            )
            {
                Flush();
                state.AddColumn();

                if (c == '`')
                    state.ToggleMultiLineStringLiteral();
                else
                    state.ToggleStringLiteral();

                state.ResetSize();
            } else
            {
                throw ADT::Exception::UnexpectedToken(state.GetLine(), state.GetColumn());
            }

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
