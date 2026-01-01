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

#include "Environment/Lexer/Except.h"
#include "Shared/LexerState.h"

#include "Environment/Lexer/Lexer.h"
#include "Environment/Lexer/Map.h"
#include "Environment/Lexer/Token.h"

namespace Typed::Environment::Util
{
    inline void FlushToken(
        const Celery::Str::String &source,
        Lexer::TokenStream &stream,
        Lexer::LexerState &state
    )
    {
        // No token to flush
        if (state.Len == 0)
        {
            return;
        }

        auto source_ptr = source.Ptr() + state.Start;

        Lexer::Token token;
        token.value = Celery::Str::External(source_ptr, state.Len);

        if (state.StringLiteral)
        {
            token.type = Lexer::Token::Type::StringLiteral;
        } else
        {
            // Find using the token map
            const auto it = Lexer::Map.find(token.value);
            if (it != Lexer::Map.end())
            {
                token.type = it->second;
            } else if (state.Identifier)
            {
                token.type = Lexer::Token::Type::Identifier;
            } else
            {
                throw Lexer::Exception(state);
            }
        }

        stream.PushBack(token);

        // Reset state
        state.Len = 0;
    }
}