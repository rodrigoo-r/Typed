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

void Walker::While(
    ProcedureRef procedure,
    VariableStack &stack,
    TreePtr body
)
{
    auto &cond = body->children[0];
    auto &then = body->children[1];

    while (true)
    {
        // Break when the condition becomes false
        if (!EvaluateCondition(stack, cond)) break;

        // Run the body
        Body(procedure, then, stack);
    }
}
