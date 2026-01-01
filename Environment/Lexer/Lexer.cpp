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

#include "Lexer.h"

#include "Environment/Util/FlushToken.h"
#include "Environment/Util/IsIdentifier.h"
#include "Environment/Util/IsWhitespace.h"
#include "Except.h"
#include "State.h"

using namespace Typed::Environment;

Lexer::TokenStream Lexer::Tokenize(
    Celery::Str::String &source
)
{
    TokenStream stream;
    State state;

    for (auto i = 0; i < source.Len(); i++)
    {
        const auto &ch = source[i];
        if (state.Len == 0)
        {
            // Start new token
            state.Start = i;
            state.StringLiteral = false;
            state.Identifier = false;
        }

#       ifdef _WIN32
        // Ignore carriage returns
        if (ch == '\r')
        {
            continue;
        }
#       endif

        if (ch == '\n')
        {
            // Flush any pending token
            Util::FlushToken(
                source,
                stream,
                state
            );

            // New line
            state.Line++;
            state.Column = 1;
            continue;
        }

        // Skip whitespace outside string literals
        if (!state.StringLiteral && Util::IsWhitespace(ch))
        {
            continue;
        }

        // Detect identifiers
        if (state.Len == 0 && Util::IsIdentifier(ch))
        {
            state.Identifier = true;
        }

        // Detect string literals
        if (ch == '"')
        {
            if (state.StringLiteral)
            {
                // End of string literal
                Util::FlushToken(
                    source,
                    stream,
                    state
                );

                state.StringLiteral = false;
                continue;
            }

            state.StringLiteral = true;
            continue;
        }

        // Break on punctuation
        if (ch == '=')
        {
            Util::FlushToken(
                source,
                stream,
                state
            );

            state.Len = 1;
            Util::FlushToken(
                source,
                stream,
                state
            );

            continue;
        }

        // Validate identifier characters
        if (state.Identifier && !Util::IsIdentifier(ch))
        {
            throw Exception(state);
        }

        state.Len++;
        state.Column++;
    }

    // Flush any pending token
    Util::FlushToken(
        source,
        stream,
        state
    );

    return stream;
}
