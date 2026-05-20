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

#include "ADT/Exception/MismatchedArgCount.h"
#include "ADT/Exception/MismatchedType.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void Walker::Procedure(
    ProcedureRef procedure,
    VariableMap &args,
    TreePtr trace
)
{
    auto line =
        trace == nullptr ?
            1 : trace->line;

    auto column =
        trace == nullptr ?
            1 : trace->column;

    // Make sure there's the same amount of args
    // as expected
    if (procedure.arguments.size() != args.size())
    {
        throw ADT::Exception::MismatchedArgCount(
            line,
            column
        );
    }

    // Initialize the stack for this procedure
    VariableMap stack;

    // Push all args to the stack
    for (auto &[name, arg] : args)
    {
        // Find the expected type
        auto expected = procedure.arguments.at(name);
        if (expected != arg.type)
        {
            throw ADT::Exception::MismatchedType(
                line,
                column
            );
        }

        stack.try_emplace(name, std::move(arg));
    }

    // Begin execution
    for (auto ast : procedure.body->children)
    {
        Expression(stack, ast);
    }
}
