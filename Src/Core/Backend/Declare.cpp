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
// Created by Rodrigo on 5/21/26.
//

#include "Support/Runtime/TypeChecker.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void Walker::Declare(
    VariableStack &stack,
    TreePtr body
)
{
    // Note: redefining variables is allowed in Typed
    auto &name = body->children[0]->value;
    auto &type = body->children[1]->type;
    auto &value = body->children[2];

    auto obj = Expression(stack, value);

    // Do type checking
    Support::Runtime::TypeCheck(
        type == ADT::Lang::ASTType::String ?
            ADT::Runtime::ObjectType::String :
        type == ADT::Lang::ASTType::Integer ?
            ADT::Runtime::ObjectType::Integer :
        type == ADT::Lang::ASTType::Float ?
            ADT::Runtime::ObjectType::Float :
        ADT::Runtime::ObjectType::Boolean,
        obj.type,
        body->line,
        body->column
    );

    stack[name] = std::move(obj);
}