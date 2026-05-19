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

#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::CallArgs(
    TokenStreamView &input,
    ExprQueue &queue
)
{
    auto args = AllocateBase(input.Peek(), ADT::Lang::ASTType::Arguments);

    // Collect and parse arguments
    while (input.HasNext())
    {
        auto start = input.Pos();
        Celery::Trait::VeryLarge size = 0;

        // Create the argument AST
        auto arg = AllocateBase(input.Peek(), ADT::Lang::ASTType::Argument);
        args->children.PushBack(arg);

        while (input.HasNext())
        {
            auto &token = input.Next();

            // Split at delimiter
            if (token.type == ADT::Lang::TokenType::Comma)
            {
                // Create the view and push it
                TokenStreamView view{
                    input.Ptr() + start,
                    size
                };

                queue.EmplaceBack(view, arg);
                start = input.Pos();
                size = 0;
            } else
            {
                size++;
            }
        }

        // Add the last arg
        if (size == 0) break;

        TokenStreamView view{
            input.Ptr() + start,
            size
        };

        queue.EmplaceBack(view, arg);
    }

    return args;
}
