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

#include "Shared/Except/Agnostic.h"
#include "Shared/Stream/TokenStream.h"
#include "State.h"
#include "TokenMap.h"

namespace Typed::Shared::Lexer
{
    template <typename Value>
    void FlushToken(
        const Celery::Str::String &source,
        Stream::TokenStream<Value> &stream,
        State &state,
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
        token.Value = Celery::Str::External(source_ptr, state.Len);

        if (state.StringLiteral)
        {
            token.Kind = Value::Type::StringLiteral;
        } else
        {
            // Find using the token map
            const auto it = map.find(token.Value);
            if (it != map.end())
            {
                token.Kind = it->second;
            } else if (state.Identifier)
            {
                token.Kind = Value::Type::Identifier;
            } else
            {
                throw AgnosticException<Value>(state);
            }
        }

        stream.PushBack(token);

        // Reset state
        state.Len = 0;
    }
}