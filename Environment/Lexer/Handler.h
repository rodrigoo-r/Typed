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
// Created by rodrigo on 1/2/26.
//

#pragma once
#include "Map.h"
#include "Shared/Except/Agnostic.h"
#include "Shared/Lexer/AgnosticHandler.h"
#include "Token.h"

namespace Typed::Environment::Lexer
{
    inline Shared::Lexer::AgnosticHandler<
        Token,
        1
    > Handler =
    {
        .Map = Map,
        .Punctuation = { '=' },
        .StringLiteral = '"',
        .NewlineHandler = [](Shared::Lexer::State &state)
        {
            if (state.StringLiteral)
            {
                throw Shared::AgnosticException<Token>(state);
            }

            return true;
        }
    };
}