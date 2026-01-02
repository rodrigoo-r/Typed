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

#include <Celery/Io/Io.h>

#include "Runtime/Engine/Rule/Block/Block.h"
#include "Runtime/Engine/Rule/Block/Launcher.h"
#include "Runtime/Engine/Writer/Stdout.h"

using namespace Typed::Runtime::Engine;

void Rule::Procedure(Core::Parser::AST *proc, Environment::Env &env)
{
    auto &children = proc->Children;

    for (auto &child : children)
    {
        switch (child->Kind)
        {
            case Core::Parser::AST::Rule::Block:
            {
                BlockLauncher(child, env);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}
