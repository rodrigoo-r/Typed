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
#include "Support/Lang/TokenMap.h"

using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Lexer;

void Machine::Flush()
{
    auto start = state.GetStart();
    auto size = state.GetSize();
    auto ptr = contents.Ptr() + start;
    ADT::Lang::Token token{
            {
                state.GetLine(),
                state.GetColumn()
            },
            Celery::Str::External{ptr, size},
            ADT::Lang::TokenType::Add
        };

    state.SetStart(contents.Pos());
    if (size == 0 && !state.IsStringLiteral())
    {
        state.Reset();
        return;
    }

    if (state.IsStringLiteral())
    {
        token.type = ADT::Lang::TokenType::StringLiteral;
    } else if (state.IsFloatLiteral())
    {
        token.type = ADT::Lang::TokenType::NumberLiteral;
    } else if (state.IsNumberLiteral())
    {
        token.type = ADT::Lang::TokenType::NumberLiteral;
    } else if (
        state.IsIdentifier() ||
        (
            token.value.Size() == 1 && (
                token.value[0] == ';' ||
                token.value[0] == ','
            )
        )
    )
    {
        // Find the token type and assign the appropriate type
        auto it = Support::Lang::TokenMap.find(token.value);
        if (it != Support::Lang::TokenMap.end())
        {
            token.type = it->second;
        }
        else
        {
            token.type = ADT::Lang::TokenType::Identifier;
        }
    } else
    {
        // Unknown token, throw an exception
        throw ADT::Exception::UnknownToken(
            state.GetLine(),
            state.GetColumn()
        );
    }

    tokens.PushBack(std::move(token));
    state.Reset();
    start = contents.Pos();
}
