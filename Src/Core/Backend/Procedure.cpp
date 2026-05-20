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
    ADT::List::Object &args,
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
    if (procedure.arguments.Size() != args.Size() && !procedure.variadic)
    {
        throw ADT::Exception::MismatchedArgCount(
            line,
            column
        );
    }

    // Initialize the stack for this procedure
    VariableMap stack;

    // Push all args to the stack
    for (auto i = 0; i < args.Size(); ++i)
    {
        auto &arg = args[i];
        auto &expected = procedure.arguments[i];

        // Find the expected type
        if (
            expected.type != arg.type &&
            expected.type != ADT::Runtime::ObjectType::Any
        )
        {
            throw ADT::Exception::MismatchedType(
                line,
                column
            );
        }

        // Don't use the stack if the procedure is native
        if (procedure.native == nullptr)
            stack.try_emplace(expected.name, std::move(arg));
    }

    // Execute the procedure directly if it's native
    if (procedure.native != nullptr)
    {
        procedure.native(args);
        return;
    }

    // Begin execution
    for (auto ast : procedure.body->children)
    {
        switch (ast->type)
        {
            case ADT::Lang::ASTType::Expression:
            {
                Expression(stack, ast);
                break;
            }

            case ADT::Lang::ASTType::Declare:
            {
                break;
            }

            default: break;
        }
    }
}
