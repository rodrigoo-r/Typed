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
#include <ankerl/unordered_dense.h>
#include <Celery/String/External.h>
#include <Celery/Misc/Hash.h>
#include <Celery/Misc/StringEqual.h>

#include "Token.h"

namespace Typed::Environment::Lexer
{
    using TokenMap = ankerl::unordered_dense::map<
        Celery::Str::External,
        Token::Type,
        Celery::Misc::Hash,
        Celery::Misc::StringEquality
    >;

    TokenMap Map = {
        {
            "=",
            Token::Type::Equal
        }
    };
}