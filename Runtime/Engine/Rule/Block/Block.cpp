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
#include <Celery/Io/Io.h>

#include "Core/Parser/Util/AllocateFrom.h"
#include "Runtime/Engine/Rule/Embed/Embed.h"
#include "Runtime/Engine/Rule/Foreach/Foreach.h"
#include "Runtime/Engine/Rule/Pull/Pull.h"

using namespace Typed::Runtime::Engine;

void Rule::Block(
    Core::Parser::AST *block,
    Scope &scope
)
{
    auto &children = block->Children;

    for (auto &child : children)
    {
        switch (child->Kind)
        {
        case Core::Parser::AST::Rule::Embed:
        {
            Embed(child, scope);
            break;
        }

        case Core::Parser::AST::Rule::Foreach:
        {
            Foreach(
                child,
                scope
            );
            break;
        }

        case Core::Parser::AST::Rule::Pull:
        {
            Pull(
                child,
                scope
            );
            break;
        }

        default:
        {
            break;
        }
        }
    }
}
