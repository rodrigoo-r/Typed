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
// Created by Rodrigo on 5/20/26.
//

#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

ADT::Runtime::Object Walker::Expression(
    VariableMap &stack,
    TreePtr body
)
{
    auto &expr = body->children[0];

    switch (expr->type)
    {
        case ADT::Lang::ASTType::Expression:
        {
            return Expression(stack, expr);
        }

        case ADT::Lang::ASTType::Call:
        {
            break;
        }

        case ADT::Lang::ASTType::Add:
        {
            break;
        }

        case ADT::Lang::ASTType::Sub:
        {
            break;
        }

        case ADT::Lang::ASTType::Mul:
        {
            break;
        }

        case ADT::Lang::ASTType::Div:
        {
            break;
        }

        case ADT::Lang::ASTType::StringLiteral:
        {
            break;
        }

        case ADT::Lang::ASTType::FalseLiteral:
        {
            break;
        }

        case ADT::Lang::ASTType::TrueLiteral:
        {
            break;
        }

        case ADT::Lang::ASTType::FloatLiteral:
        {
            break;
        }

        case ADT::Lang::ASTType::NumberLiteral:
        {
            break;
        }

        case ADT::Lang::ASTType::Identifier:
        {
            break;
        }

        default: break;
    }

    return {};
}
