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

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::BooleanOperation(
    TokenStreamView &input,
    TreePtr result
)
{
    auto &op_token = input.Peek();
    auto op = Allocate(ADT::Lang::ASTType::Root);

    // Collect tokens until we find a delimiter
    Celery::Trait::VeryLarge start = input.Pos();
    Celery::Trait::VeryLarge size = 0;
    auto found_delim = false;

    while (input.HasNext())
    {
        auto &next = input.Next();
        if (
            next.type == ADT::Lang::TokenType::And ||
            next.type == ADT::Lang::TokenType::Or
        )
        {
            found_delim = true;
            break;
        }

        size++;
    }

    // Make sure we found the delimiter
    if (!found_delim)
    {
        throw ADT::Exception::UnexpectedToken(
            input.Curr().line,
            input.Curr().column
        );
    }

    // Construct the view
    ADT::Stream::External<ADT::Lang::Token> stream{
        input.Ptr() + start,
        size
    };

    switch (op_token.type)
    {
        case ADT::Lang::TokenType::Equal:
        {
            op->type = ADT::Lang::ASTType::Equal;
            return Equal(stream);
        }

        case ADT::Lang::TokenType::Greater:
        {
            op->type = ADT::Lang::ASTType::Greater;
            return Greater(stream);
        }

        case ADT::Lang::TokenType::Less:
        {
            op->type = ADT::Lang::ASTType::Less;
            return Less(stream);
        }

        default:
        {
            throw ADT::Exception::UnexpectedToken(
                op->line,
                op->column
            );
        }
    }
}
