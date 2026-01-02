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

#pragma once
#include "Block.h"
#include "Core/Parser/Ast.h"
#include "Environment/Env.h"
#include "Runtime/Engine/Scope/Scope.h"
#include "Runtime/Engine/Writer/Stdout.h"

namespace Typed::Runtime::Engine::Rule
{
    inline void BlockLauncher(
        Core::Parser::AST *ast,
        Environment::Env &env
    )
    {
        Writer::Stdout default_writer;
        Scope scope;
        scope.Writer = &default_writer;

        for (auto &[key, val] : env)
        {
            scope.Symbols.emplace(key, val);
        }

        Block(ast, scope);
    }
}
