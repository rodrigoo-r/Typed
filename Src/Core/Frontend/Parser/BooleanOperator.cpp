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

#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

int GetPrecedence(ADT::Lang::TokenType op)
{
    if (op == ADT::Lang::TokenType::And)
    {
        return 2;
    }

    return 1;
}

ADT::Lang::ASTType GetASTType(ADT::Lang::TokenType type)
{
    switch (type)
    {
        case ADT::Lang::TokenType::And:
        {
            return ADT::Lang::ASTType::And;
        }

        case ADT::Lang::TokenType::Or:
        {
            return ADT::Lang::ASTType::Or;
        }

        default:
            return ADT::Lang::ASTType::Root;
    }
}

Machine::TreePtr Machine::BooleanOperator(
    TokenStreamView &input,
    TreePtr result,
    ExprQueue &queue
)
{
    TreePtr op = nullptr;
    ADT::Lang::TokenType last_op = input.Peek().type;

    while (input.HasNext())
    {
        auto &op_token = input.Peek();
        if (
            op_token.type != ADT::Lang::TokenType::And &&
            op_token.type != ADT::Lang::TokenType::Or
        ) return result;

        // Consume the token
        op = AllocateBase(
            input.Next(),
            GetASTType(op_token.type)
        );

        auto stream = ExtractUntilBoolean(input, false);
        auto expr = AllocateBase(op_token, ADT::Lang::ASTType::Expression);
        auto last_precedence = GetPrecedence(last_op);
        auto current_precedence = GetPrecedence(op_token.type);

        // Case 1: Current operator has lower or same precedence
        if (current_precedence <= last_precedence)
        {
            // Just wrap in a new binary operator
            op->children.PushBack(result);
            op->children.PushBack(expr);
            queue.EmplaceBack(stream, expr);

            result = op;
            last_op = op_token.type;
        }
        else
        {
            // Take the current RHS of the lower-precedence operator
            auto last_rhs = result->children.PopBackMove();

            // Build the higher-precedence subtree
            op->children.PushBack(last_rhs);
            op->children.PushBack(expr);

            queue.EmplaceBack(stream, expr);

            // Reattach it as the RHS of the existing operator
            result->children.PushBack(op);
        }
    }

    return result;
}
