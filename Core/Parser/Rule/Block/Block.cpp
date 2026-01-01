/*
        ==== The Zelix Programming Language ====
---------------------------------------------------------
  - This file is part of the Zelix Programming Language
    codebase. Zelix is a fast, statically-typed and
    memory-safe programming language that aims to
    match native speeds while staying highly ergonomic.
---------------------------------------------------------
  - Zelix is categorized as free software; you can
    redistribute it and/or modify it under the terms of
    the Apache License, Version 2.0.
---------------------------------------------------------
  - You should have received a copy of the Apache
    License v2.0 along with Zelix. If not, see
    <http://www.apache.org/licenses/LICENSE-2.0>.
*/

//
// Created by rodrigo on 1/1/26.
//

#include "Block.h"
#include "Core/Parser/Queue/Block.h"

#include "Core/Parser/Rule/Embed/Embed.h"
#include "Core/Parser/Rule/Foreach/Foreach.h"
#include "Core/Parser/Rule/Pull/Pull.h"
#include "Core/Parser/Util/AllocateFrom.h"
#include "Shared/Stream/Expect.h"

using namespace Typed::Core;

void Parser::Rule::Block(
    AST *root,
    Lexer::TokenStream &stream
)
{
    auto block = Util::AllocateFrom(
        stream,
        AST::Rule::Block
    );
    root->Children.PushBack(block);

    // Create a queue to parse nested blocks
    Queue::Block queue;
    queue.PushBack(block);

    while (!queue.Empty())
    {
        auto &curr = queue.Back();
        auto done = false;

        while (!done && stream.HasNext())
        {
            auto &next = stream.Next();

            switch (next.Kind)
            {
                case Lexer::Token::Type::Embed:
                {
                    Embed(
                        curr,
                        stream
                    );
                    break;
                }

                case Lexer::Token::Type::Foreach:
                {
                    Foreach(curr, stream, queue);
                    break;
                }

                case Lexer::Token::Type::Pull:
                {
                    Pull(
                        curr,
                        stream
                    );
                    break;
                }

                case Lexer::Token::Type::End:
                {
                    done = true;
                    queue.PopBack();
                    break;
                }

                default:
                {
                    throw Shared::AgnosticException(stream);
                }
            }
        }

        if (done) continue;
        throw Shared::AgnosticException(stream);
    }
}
