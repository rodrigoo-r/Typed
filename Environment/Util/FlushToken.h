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

#include <celery/string/string.h>
#include "Environment/Lexer/State.h"

#include "Environment/Lexer/Lexer.h"
#include "Environment/Lexer/Token.h"

namespace Typed::Environment::Util
{
    inline void FlushToken(
        const Celery::Str::String &source,
        Lexer::TokenStream &stream,
        const Lexer::Token::Type type,
        Lexer::State &state
    )
    {
        // No token to flush
        if (state.Len == 0)
        {
            return;
        }

        auto source_ptr = source.Ptr() + state.Start;

        Lexer::Token token;
        token.type = type;
        token.value = Celery::Str::External(source_ptr, state.Len);

        stream.PushBack(token);

        // Reset state
        state.Len = 0;
    }
}