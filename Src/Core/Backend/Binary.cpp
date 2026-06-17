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
// Created by Rodrigo on 5/23/26.
//

#include "Support/Equality/Object.h"
#include "Support/Runtime/GetObjValue.h"
#include "Support/Runtime/TypeChecker.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

bool PerformBooleanOp(
    ADT::Lang::AST *body,
    auto left,
    auto right
)
{
    switch (body->type)
    {
        case ADT::Lang::ASTType::Less:
        {
            return left < right;
        }

        case ADT::Lang::ASTType::Greater:
        {
            return left > right;
        }

        case ADT::Lang::ASTType::LessEqual:
        {
            return left <= right;
        }

        case ADT::Lang::ASTType::GreaterEqual:
        {
            return left >= right;
        }

        default: return false;
    }
}

ADT::Runtime::Object Walker::Binary(
    VariableStack &stack,
    TreePtr body
)
{
    auto &left = body->children[0];
    auto &right = body->children[1];

    auto is_bool = body->type == ADT::Lang::ASTType::And ||
        body->type == ADT::Lang::ASTType::Or;

    auto is_equal = body->type == ADT::Lang::ASTType::Equal;

    // Evaluate both sides
    auto left_obj = Expression(stack, left);
    auto right_obj = Expression(stack, right);

    // Do type checking for boolean ops
    if (is_bool)
    {
        Support::Runtime::TypeCheck(
            ADT::Runtime::ObjectType::Boolean,
            left_obj.type,
            left->line,
            left->column
        );

        Support::Runtime::TypeCheck(
            ADT::Runtime::ObjectType::Boolean,
            right_obj.type,
            right->line,
            right->column
        );
    }
    // For comparisons
    else if (is_equal)
    {
        // Make sure they're both the same type
        Support::Runtime::TypeCheck(
            left_obj.type,
            right_obj.type,
            right->line,
            right->column
        );
    }
    // For arithmetic ops
    else
    {
        // Make sure it's either Integer or Float
        if (
            left_obj.type != ADT::Runtime::ObjectType::Integer &&
            left_obj.type != ADT::Runtime::ObjectType::Float
        )
        {
            throw ADT::Exception::MismatchedType(
                left->line,
                left->column
            );
        }

        // Do type checking on the RHS
        Support::Runtime::TypeCheck(
            left_obj.type,
            right_obj.type,
            right->line,
            right->column
        );
    }

    bool result = false;

    if (is_bool)
    {
        bool left_bool = Support::Runtime::GetBoolObj(left_obj);
        bool right_bool = Support::Runtime::GetBoolObj(right_obj);
        if (body->type == ADT::Lang::ASTType::And)
        {
            result = left_bool && right_bool;
        } else
        {
            result = left_bool || right_bool;
        }
    }
    else if (is_equal)
    {
        result = Support::Equality::Object::Equals(left_obj, right_obj);
    }
    else
    {
        if (left_obj.type == ADT::Runtime::ObjectType::Integer)
        {
            auto &left_int = Support::Runtime::GetIntObj(left_obj);
            auto &right_int = Support::Runtime::GetIntObj(right_obj);
            result = PerformBooleanOp(body, left_int, right_int);
        } else
        {
            auto &left_float = Support::Runtime::GetFloatObj(left_obj);
            auto &right_float = Support::Runtime::GetFloatObj(right_obj);
            result = PerformBooleanOp(body, left_float, right_float);
        }
    }

    return  {
        ADT::Runtime::ObjectType::Boolean,
        result
    };
}