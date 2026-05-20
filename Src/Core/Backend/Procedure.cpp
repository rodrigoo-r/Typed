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
#include "Support/Runtime/TypeChecker.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void ProcessArg(
    ADT::List::Object &args,
    Walker::ProcedureRef procedure,
    Celery::Trait::VeryLarge line,
    Celery::Trait::VeryLarge column,
    Celery::Trait::VeryLarge i,
    Walker::VariableMap &stack
)
{
    // Make sure the procedure has enough arguments
    if (procedure.arguments.Size() <= i)
    {
        throw ADT::Exception::MismatchedArgCount(
            line,
            column
        );
    }

    auto &arg = args[i];
    auto &expected = procedure.arguments[i];
    Support::Runtime::TypeCheck(
        expected.type,
        arg.type,
        line,
        column
    );

    // Don't use the stack if the procedure is native
    if (procedure.native == nullptr)
        stack.try_emplace(expected.name, std::move(arg));
}

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
    Celery::Trait::SignedVeryLarge args_size = args.Size();
    if (procedure.variadic)
    {
        // Get the index where the arg type changes
        auto last = args[0].type;
        Celery::Trait::SignedVeryLarge change = -1;

        for (auto i = 0; i < args.Size(); ++i)
        {
            auto &arg = args[i];
            if (last != arg.type)
            {
                change = i;
                break;
            }

            last = arg.type;
        }

        // Do tye checking until the idx where it changes
        args_size = change;

        // Make sure all other args are the same type
        if (change == -1) change = 0;
        for (auto i = change; i < args.Size(); ++i)
        {
            auto &arg = args[i];

            Support::Runtime::TypeCheck(
                procedure.arguments[procedure.arguments.Size() - 1].type,
                arg.type,
                line,
                column
            );
        }
    }

    for (auto i = 0; i < args_size; ++i)
    {
        ProcessArg(args, procedure, line, column, i, stack);
    }

    // Execute the procedure directly if it's native
    if (procedure.native != nullptr)
    {
        procedure.native(args, trace);
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
