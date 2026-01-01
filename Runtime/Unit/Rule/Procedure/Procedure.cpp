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

#include "Procedure.h"

#include "Shared/Except/Agnostic.h"

using namespace Typed::Runtime::Unit;

void Rule::Procedure(
    Symbol::Unit &unit,
    Core::Parser::AST *proc
)
{
    auto &name = proc->Value;
    auto emplace = unit.Procedures.emplace(
        name,
        proc
    );

    if (!emplace.second)
    {
        // Procedure already exists
        throw Celery::Except::Exception(name.Ptr());
    }
}
