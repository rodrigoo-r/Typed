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

void Walker::ConditionGroup(
    ProcedureRef procedure,
    VariableStack &stack,
    TreePtr body
)
{
    for (auto &child : body->children)
    {
        if (child->type == ADT::Lang::ASTType::Else)
        {
            // Execute the body directly
            Body(procedure, child->children[0], stack);
        } else
        {
            auto res = If(procedure, stack, child);

            // Stop execution if the condition executed
            if (res) return;
        }
    }
}
