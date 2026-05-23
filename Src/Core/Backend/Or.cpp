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

ADT::Runtime::Object Walker::Or(
    VariableStack &stack,
    TreePtr body
)
{
    auto &left = body->children[0];
    auto &right = body->children[1];

    // Evaluate both sides
    auto left_obj = Expression(stack, left);
    auto right_obj = Expression(stack, right);

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

    return  {
        ADT::Runtime::ObjectType::Boolean,
        Support::Runtime::GetBoolObj(left_obj) ||
            Support::Runtime::GetBoolObj(right_obj)
    };
}
