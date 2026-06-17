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
// Created by Rodrigo on 5/19/26.
//

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"
#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::CallArgs(
    TokenStreamView &input,
    ExprQueue &queue
)
{
    auto args = AllocateBase(
        Support::Stream::SafePeek(input),
        ADT::Lang::ASTType::Arguments
    );

    auto start = input.Pos();
    Celery::Trait::VeryLarge size = 0;
    Celery::Trait::VeryLarge call_nest = 1;

    // Create the argument AST
    auto arg = AllocateBase(
        Support::Stream::SafePeek(input),
        ADT::Lang::ASTType::Argument
    );
    args->children.PushBack(arg);

    while (input.HasNext())
    {
        auto &token = input.Next();

        // Split at delimiter
        if (
            token.type == ADT::Lang::TokenType::Comma &&
            call_nest == 1
        )
        {
            // Create the view and push it
            TokenStreamView view{
                input.Ptr() + start,
                size
            };

            // Make sure the input isn't empty
            if (view.Empty())
            {
                throw ADT::Exception::UnexpectedToken(
                    input.Curr().line,
                    input.Curr().column
                );
            }

            queue.EmplaceBack(view, arg);
            start = input.Pos();
            size = 0;

            arg = AllocateBase(
                Support::Stream::SafePeek(input),
                ADT::Lang::ASTType::Argument
            );

            args->children.PushBack(arg);
        }
        else if (token.type == ADT::Lang::TokenType::Call)
        {
            call_nest++;
            size++;
        }
        else if (token.type == ADT::Lang::TokenType::EndCall)
        {
            call_nest--;
            if (call_nest == 0) break;

            size++;
        }
        else
        {
            size++;
        }
    }

    // Make sure the nest size is 0 at the end
    if (call_nest != 0)
    {
        throw ADT::Exception::UnexpectedToken(
            input.Curr().line,
            input.Curr().column
        );
    }

    // Add the last arg
    if (size == 0) return args;

    TokenStreamView view{
        input.Ptr() + start,
        size
    };

    queue.EmplaceBack(view, arg);

    return args;
}
