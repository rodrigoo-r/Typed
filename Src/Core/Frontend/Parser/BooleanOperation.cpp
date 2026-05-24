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
#include "Support/Printer/ASTPrinter.h"
#include "Support/Stream/SafeNext.h"
#include "Support/Stream/SafePeek.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::BooleanOperation(
    TokenStreamView &input,
    TreePtr result,
    ExprQueue &queue
)
{
    auto &op_token = Support::Stream::SafePeek(input);
    auto op = AllocateBase(
        Support::Stream::SafeNext(input),
        ADT::Lang::ASTType::Root
    );

    // Wrap the result inside an expression
    auto lhs_expr = AllocateBase(op_token, ADT::Lang::ASTType::Expression);
    lhs_expr->children.PushBack(result);
    op->children.PushBack(lhs_expr);

    auto stream = ExtractUntilBoolean(input, false);
    auto expr = AllocateBase(op_token, ADT::Lang::ASTType::Expression);
    queue.EmplaceBack(stream, expr);
    op->children.PushBack(expr);

    switch (op_token.type)
    {
        case ADT::Lang::TokenType::Equal:
        {
            op->type = ADT::Lang::ASTType::Equal;
            break;
        }

        case ADT::Lang::TokenType::Greater:
        {
            op->type = ADT::Lang::ASTType::Greater;
            break;
        }

        case ADT::Lang::TokenType::Less:
        {
            op->type = ADT::Lang::ASTType::Less;
            break;
        }

        case ADT::Lang::TokenType::GreaterEqual:
        {
            op->type = ADT::Lang::ASTType::GreaterEqual;
            break;
        }

        case ADT::Lang::TokenType::LessEqual:
        {
            op->type = ADT::Lang::ASTType::LessEqual;
            break;
        }

        default:
        {
            throw ADT::Exception::UnexpectedToken(
                op->line,
                op->column
            );
        }
    }

    return op;
}
