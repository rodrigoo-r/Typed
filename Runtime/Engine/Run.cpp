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

#include "Run.h"

#include "Rule/Procedure/Procedure.h"

using namespace Typed::Runtime;

void Engine::Run(Symbol::Unit &unit, Environment::Env &env)
{
    Celery::Str::External main_str = "Main";
    auto main_proc_it = unit.Procedures.find(main_str);

    if (main_proc_it == unit.Procedures.end())
    {
        // Main procedure not found
        throw Celery::Except::Exception(main_str.Ptr());
    }

    Rule::Procedure(main_proc_it->second, env);
}
