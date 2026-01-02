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
#include <Celery/Trait/Default.h>
#include <array>
#include <functional>

#include "State.h"
#include "TokenMap.h"

namespace Typed::Shared::Lexer
{
    template <
        typename Value,
        Celery::Trait::VeryLarge Size
    >
    struct AgnosticHandler
    {
        using PunctuationList =
            std::array<char, Size>;

        using Handler =
            std::function<bool(State &)>;

        TokenMap<Value> &Map;
        PunctuationList Punctuation;
        char StringLiteral;
        Handler NewlineHandler;
    };
}