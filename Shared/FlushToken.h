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

#include <Celery/String/String.h>

#include "LexerExceptcion.h"
#include "Shared/LexerState.h"
#include "TokenMap.h"
#include "TokenStream.h"

#include "Environment/Lexer/Lexer.h"
#include "Environment/Lexer/Map.h"
#include "Environment/Lexer/Token.h"

namespace Typed::Shared
{
    template <typename Value>
    inline void FlushToken(
        const Celery::Str::String &source,
        TokenStream<Value> &stream,
        LexerState &state,
        TokenMap<Value> &map
    )
    {
        // No token to flush
        if (state.Len == 0)
        {
            return;
        }

        auto source_ptr = source.Ptr() + state.Start;

        Value token;
        token.value = Celery::Str::External(source_ptr, state.Len);

        if (state.StringLiteral)
        {
            token.type = Value::Type::StringLiteral;
        } else
        {
            // Find using the token map
            const auto it = map.find(token.value);
            if (it != map.end())
            {
                token.type = it->second;
            } else if (state.Identifier)
            {
                token.type = Value::Type::Identifier;
            } else
            {
                throw LexerException<Value>(state);
            }
        }

        stream.PushBack(token);

        // Reset state
        state.Len = 0;
    }
}