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
// Created by Rodrigo on 5/22/26.
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
    op->children.PushBack(result);

   auto stream = ExtractUntilBoolean(input);

    switch (op_token.type)
    {
        case ADT::Lang::TokenType::Equal:
        {
            op->type = ADT::Lang::ASTType::Equal;
            return Equal(stream, op);
        }

        case ADT::Lang::TokenType::Greater:
        {
            op->type = ADT::Lang::ASTType::Greater;
            return Greater(stream, op);
        }

        case ADT::Lang::TokenType::Less:
        {
            op->type = ADT::Lang::ASTType::Less;
            return Less(stream, op);
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
