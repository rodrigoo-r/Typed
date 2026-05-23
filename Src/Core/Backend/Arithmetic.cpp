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

#include "ADT/Exception/MismatchedType.h"
#include "ADT/Exception/UnknownSymbol.h"
#include "Support/Runtime/GetObjValue.h"
#include "Support/Strconv/ParseFloat.h"
#include "Support/Strconv/ParseInt.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void PerformOp(
    auto &lhs,
    auto &val,
    ADT::Lang::ASTType type
)
{
    switch (type)
    {
        case ADT::Lang::ASTType::Add:
        {
            val += lhs;
            break;
        }

        case ADT::Lang::ASTType::Sub:
        {
            val -= lhs;
            break;
        }

        case ADT::Lang::ASTType::Mul:
        {
            val *= lhs;
            break;
        }

        case ADT::Lang::ASTType::Div:
        {
            val /= lhs;
            break;
        }

        default: break;
    }
}

void Walker::Arithmetic(
    VariableStack &stack,
    TreePtr body
)
{
    auto &name = body->children[0]->value;
    auto &value = body->children[1]->value;

    // Get the variable
    auto var_it = stack.Get(name);
    if (var_it.IsEnd())
    {
        throw ADT::Exception::UnknownSymbol(
            body->line,
            body->column
        );
    }

    auto &var = var_it.it->second;

    // Type check the variable
    if (
        var.type != ADT::Runtime::ObjectType::Float &&
        var.type != ADT::Runtime::ObjectType::Integer
    )
    {
        throw ADT::Exception::MismatchedType(
            body->line,
            body->column
        );
    }

    // Parse the value
    if (var.type == ADT::Runtime::ObjectType::Float)
    {
        auto lhs = Support::Strconv::ParseFloat(value);
        auto &val = Support::Runtime::GetFloatObj(var);

        PerformOp(lhs, val, body->type);
    }
    else
    {
        auto lhs = Support::Strconv::ParseInt(value);
        auto &val = Support::Runtime::GetIntObj(var);

        PerformOp(lhs, val, body->type);
    }
}
