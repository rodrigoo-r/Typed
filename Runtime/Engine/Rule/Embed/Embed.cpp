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

#include "Embed.h"

#include <Celery/Io/Io.h>

#include "Shared/String/ReplaceAll.h"

using namespace Typed::Runtime::Engine;

void Rule::Embed(
    Core::Parser::AST *embed,
    Scope &scope
)
{
    auto &children = embed->Children;
    Celery::Array::Vector<Celery::Str::External> vars;
    Celery::Str::External str;

    for (auto &child : children)
    {
        switch (child->Kind)
        {
            case Core::Parser::AST::Rule::StringLiteral:
            {
                str = child->Value;
                break;
            }

            case Core::Parser::AST::Rule::Push:
            {
                vars.PushBack(child->Value);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    // Print directly if no variables
    if (vars.Empty())
    {
        scope.Writer->Write(str);
        return;
    }

    // Replace variables
    Celery::Str::String result;
    result.Write(str.Ptr(), str.Len());

    for (auto &var : vars)
    {
        auto val_it = scope.Symbols.find(var);
        if (val_it == scope.Symbols.end())
        {
            throw Celery::Except::Exception(var.Ptr());
        }

        auto &val = val_it->second;
        Celery::Str::String lookup;
        lookup.Resize(var.Size() + 2);
        lookup += '@';
        lookup.Write(var.Ptr(), var.Size());
        lookup += '@';

        Shared::String::ReplaceAll(
            result,
            lookup.External(),
            val
        );
    }

    auto str_ext = result.External();
    scope.Writer->Write(str_ext);
}
