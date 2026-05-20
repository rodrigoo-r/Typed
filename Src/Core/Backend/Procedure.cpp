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

void Walker::Procedure(
    ProcedureRef procedure,
    VariableMap &args
)
{
    // Initialize the stack for this procedure
    VariableMap stack;

    // Push all args to the stack
    for (auto &[name, arg] : args)
    {
        stack.try_emplace(name, std::move(arg));
    }

    
}
