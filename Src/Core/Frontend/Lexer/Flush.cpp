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
            state.GetTokenLine(),
            state.GetTokenColumn()
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
        token.type = ADT::Lang::TokenType::FloatLiteral;
    } else if (state.IsNumberLiteral())
    {
        token.type = ADT::Lang::TokenType::NumberLiteral;
    } else
    {
        // Find the token type and assign the appropriate type
        auto it = Support::Lang::TokenMap.find(token.value);
        auto found = false;
        if (it != Support::Lang::TokenMap.end())
        {
            found = true;
            token.type = it->second;
            token.value = Celery::Str::External{"", 0};
        }
        else
        {
            token.type = ADT::Lang::TokenType::Identifier;
        }

        if (!state.IsIdentifier() && !found)
        {
            // Unknown token, throw an exception
            throw ADT::Exception::UnknownToken(
                state.GetLine(),
                state.GetColumn()
            );
        }
    }

    tokens.PushBack(std::move(token));
    state.Reset();
    start = contents.Pos();
}
