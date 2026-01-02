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

#include "Foreach.h"

#include <Celery/Io/Io.h>

#include "Runtime/Engine/Rule/Block/Block.h"
#include "Shared/String/Split.h"

using namespace Typed::Runtime::Engine;

void Rule::Foreach(
    Core::Parser::AST *foreach,
    Scope &scope
)
{
    auto &children = foreach->Children;
    auto &var = children[0]->Value;
    auto &iterable_ast = children[1];
    auto &body = children[2];

    // Get the iterable value from the scope
    auto iterator = scope.Symbols.find(iterable_ast->Value);
    if (iterator == scope.Symbols.end())
    {
        throw Celery::Except::Exception("Undefined iterable in foreach loop");
    }

    auto &raw = iterator->second;
    auto iterable = Shared::String::Split(raw, ",");

    // Iterate and queue
    for (auto &el : iterable)
    {
        Scope new_scope;
        new_scope.Symbols = scope.Symbols;
        new_scope.Writer = scope.Writer;

        new_scope.Symbols[var] = el;
        Block(body, new_scope);
    }
}
