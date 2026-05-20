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

#include "Support/Strconv/ParseFloat.h"
#include "Support/Strconv/ParseInt.h"
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
            return Call(stack, expr);
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
            return {
                ADT::Runtime::ObjectType::String,
                expr->value
            };
        }

        case ADT::Lang::ASTType::FalseLiteral:
        {
            return {
                ADT::Runtime::ObjectType::Boolean,
                false
            };
        }

        case ADT::Lang::ASTType::TrueLiteral:
        {
            return {
                ADT::Runtime::ObjectType::Boolean,
                true
            };
        }

        case ADT::Lang::ASTType::FloatLiteral:
        {
            return {
                ADT::Runtime::ObjectType::Float,
                Support::Strconv::ParseFloat(expr->value)
            };
        }

        case ADT::Lang::ASTType::NumberLiteral:
        {
            return {
                ADT::Runtime::ObjectType::Integer,
                Support::Strconv::ParseInt(expr->value)
            };
        }

        case ADT::Lang::ASTType::Identifier:
        {
            break;
        }

        default: break;
    }

    return {};
}
