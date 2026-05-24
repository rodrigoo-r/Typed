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
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::Type()
{
    // Get the next token and ensure it's a type
    auto &token = tokens.Next();

    switch (token.type)
    {
        case ADT::Lang::TokenType::String:
        {
            return AllocateBase(token, ADT::Lang::ASTType::String);
        }

        case ADT::Lang::TokenType::Integer:
        {
            return AllocateBase(token, ADT::Lang::ASTType::Integer);
        }

        case ADT::Lang::TokenType::Float:
        {
            return AllocateBase(token, ADT::Lang::ASTType::Float);
        }

        case ADT::Lang::TokenType::Boolean:
        {
            return AllocateBase(token, ADT::Lang::ASTType::Boolean);
        }

        case ADT::Lang::TokenType::List:
        {
            return AllocateBase(token, ADT::Lang::ASTType::List);
        }

        case ADT::Lang::TokenType::Dictionary:
        {
            return AllocateBase(token, ADT::Lang::ASTType::Dictionary);
        }

        default:
        {
            throw ADT::Exception::UnexpectedToken(
                token.line,
                token.column
            );
        }
    }
}
