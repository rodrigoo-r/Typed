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
#include <Celery/String/External.h>


#include "Shared/Trace/Trace.h"
#include "Shared/Stream/TokenStream.h"

namespace Typed::Core::Lexer
{
    struct Token : Global::Trace::Trace
    {
        enum class Type
        {
            Procedure,
            Identifier,
            Embed,
            Text,
            StringLiteral,
            End,
            Foreach,
            In,
            Pull,
            From,
            Push
        };

        Type Kind;
        Celery::Str::External Value;
    };

    using TokenStream = Shared::Stream::TokenStream<Token>;
}