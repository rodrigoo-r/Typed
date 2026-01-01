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

#include <Celery/Io/Io.h>

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
        const auto c = source[i];

        if (state.Len == 0)
        {
            state.Start = i;
        }

        // Handle newlines
        if (c == '\n')
        {
            if (state.StringLiteral)
            {
                throw Exception(state);
            }

            Util::FlushToken(
                source,
                stream,
                state
            );

            state.Line++;
            state.Column = 1;

            continue;
        }

        // Handle string literals
        if (c == '"')
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
            } else
            {
                // Start of string literal
                Util::FlushToken(
                    source,
                    stream,
                    state
                );

                state.StringLiteral = true;
            }


            continue;
        }

        // Ignore characters inside string literals
        if (state.StringLiteral)
        {
            state.Len++;
            state.Column++;
            continue;
        }

#       ifdef _WIN32
        // Ignore carriage returns
        if (c == '\r')
        {
            continue;
        }
#       endif

        // Ignore whitespace
        if (Util::IsWhitespace(c))
        {
            Util::FlushToken(
                source,
                stream,
                state
            );

            state.Column++;
            continue;
        }

        // Detect identifiers
        if (state.Len == 0 && Util::IsIdentifier(c))
        {
            state.Identifier = true;
        }
        else if (c == '=')
        {
            // Flush previous token
            Util::FlushToken(
                source,
                stream,
                state
            );

            // Add equal token
            state.Start = i;
            state.Len = 1;
            Util::FlushToken(
                source,
                stream,
                state
            );

            continue;
        }
        else if (
            (state.Identifier && !Util::IsIdentifier(c)) ||
            !state.Identifier
        )
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
