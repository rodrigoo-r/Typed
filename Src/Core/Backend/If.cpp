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

#include "ADT/Exception/UnknownProcedure.h"
#include "Support/Runtime/GetObjValue.h"
#include "Support/Runtime/TypeChecker.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

bool Walker::If(
    ProcedureRef procedure,
    VariableStack &stack,
    TreePtr body
)
{
    auto &cond = body->children[0];
    auto &then = body->children[1];

    // Evaluate the condition
    auto cond_obj = Expression(stack, cond);
    Support::Runtime::TypeCheck(
        ADT::Runtime::ObjectType::Boolean,
        cond_obj.type,
        cond->line,
        cond->column
    );

    // Run the body only if the condition evaluates to true
    if (Support::Runtime::GetBoolObj(cond_obj))
    {
        Body(procedure, then, stack);
        return true;
    }

    return false;
}
