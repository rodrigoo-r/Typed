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

#include "Pull.h"

#include <Celery/Io/Io.h>
#include <Celery/Ptr/Shared.h>

#include "Runtime/Engine/Rule/Block/Block.h"
#include "Runtime/Engine/Rule/Embed/Embed.h"
#include "Runtime/Engine/Writer/String.h"

using namespace Typed::Runtime::Engine;

void Rule::Pull(
    Core::Parser::AST *pull,
    Queue::BlockBase::OwnedDataList &list,
    Scope &scope
)
{
    auto &children = pull->Children;
    Celery::Str::External name;
    Core::Parser::AST *from = nullptr;

    for (auto &child : children)
    {
        switch (child->Kind)
        {
            case Core::Parser::AST::Rule::Identifier:
            {
                name = child->Value;
                break;
            }

            case Core::Parser::AST::Rule::Embed:
            {
                from = child;
                break;
            }

            default:
            {
                break;
            }
        }
    }

    // Create a scope with a string writer for the embed
    Scope embed_scope;
    Writer::String str_writer;
    embed_scope.Symbols = scope.Symbols;
    embed_scope.Writer = &str_writer;
    Embed(from, embed_scope);

    list.PushBack(str_writer.Handle);

    // Append the variable
    scope.Symbols[name] = list.Back()->External();
}
