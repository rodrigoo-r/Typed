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

#include "Support/Runtime/GetObjValue.h"
#include "Support/Runtime/TypeChecker.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void Walker::For(
    ProcedureRef procedure,
    VariableStack &stack,
    TreePtr body
)
{
    auto &decl = body->children[0];
    auto &from = body->children[1];
    auto &to = body->children[2];
    auto &step = body->children[3];
    auto &loop_body = body->children[4];
    auto line = body->line;
    auto column = body->column;

    auto &decl_name = decl->children[0]->value;
    auto decl_type = decl->children[1]->type;
    ADT::Runtime::ObjectType type;

    switch (decl_type)
    {
        case ADT::Lang::ASTType::Integer:
        {
            type = ADT::Runtime::ObjectType::Integer;
            break;
        }

        case ADT::Lang::ASTType::String:
        {
            type = ADT::Runtime::ObjectType::String;
            break;
        }

        case ADT::Lang::ASTType::Float:
        {
            type = ADT::Runtime::ObjectType::Float;
            break;
        }

        default:
        {
            type = ADT::Runtime::ObjectType::Boolean;
        }
    }

    // Evaluate the parts of the loop
    auto from_obj = Expression(stack, from);
    auto to_obj = Expression(stack, to);
    auto step_obj = Expression(stack, step);

    // Make sure the starting object is a number
    if (
        from_obj.type != ADT::Runtime::ObjectType::Integer &&
        from_obj.type != ADT::Runtime::ObjectType::Float
    )
    {
        throw ADT::Exception::MismatchedType(
            line,
            column
        );
    }

    Support::Runtime::TypeCheck(
        type,
        from_obj.type,
        line,
        column
    );

    Support::Runtime::TypeCheck(
        from_obj.type,
        to_obj.type,
        line,
        column
    );

    Support::Runtime::TypeCheck(
        step_obj.type,
        to_obj.type,
        line,
        column
    );

    // Create the variable
    stack.PushScope();
    stack.Emplace(decl_name, std::move(from_obj));

    // Execute the loop
    while (true)
    {
        auto var_it = stack.Get(decl_name);
        auto &var = var_it.it->second;

        // Execute the body
        Body(procedure, loop_body, stack, false);

        if (from_obj.type == ADT::Runtime::ObjectType::Integer)
        {
            auto &from_int = Support::Runtime::GetIntObj(from_obj);
            auto &to_int = Support::Runtime::GetIntObj(to_obj);
            auto &step_int = Support::Runtime::GetIntObj(step_obj);
            auto &var_int = Support::Runtime::GetIntObj(var);

            if (var_int >= to_int)
                break;

            var_int += step_int;
        } else
        {
            auto &from_float = Support::Runtime::GetFloatObj(from_obj);
            auto &to_float = Support::Runtime::GetFloatObj(to_obj);
            auto &step_float = Support::Runtime::GetFloatObj(step_obj);
            auto &var_float = Support::Runtime::GetFloatObj(var);

            if (var_float >= to_float)
                break;

            var_float += step_float;
        }
    }
}
