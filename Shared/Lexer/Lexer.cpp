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

#include "Core/Lexer/Map.h"
#include "Environment/Lexer/Map.h"
#include "FlushToken.h"
#include "Shared/Character/IsIdentifier.h"
#include "Shared/Character/IsWhitespace.h"
#include "Shared/Except/Agnostic.h"
#include "State.h"

using namespace Typed::Shared;

template <Lexer::LexerType T>
Lexer::ConditionalStream<T> Lexer::Tokenize(
    Celery::Str::String &source
)
{
    using Token = std::conditional_t<
        T == LexerType::Environment,
        Environment::Lexer::Token,
        Core::Lexer::Token
    >;

    TokenMap<Token> Map;
    if constexpr (T == LexerType::Environment)
    {
        Map = Environment::Lexer::Map;
    } else
    {
        Map = Core::Lexer::Map;
    }

    ConditionalStream<T> stream;
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
            if constexpr (T == LexerType::Environment)
            {
                if (state.StringLiteral)
                {
                    throw AgnosticException<Token>(state);
                }
            } else
            {
                if (!state.StringLiteral)
                {
                    FlushToken(
                        source,
                        stream,
                        state,
                        Map
                    );
                }
            }

            state.Line++;
            state.Column = 1;

            continue;
        }

        // Handle string literals
        if (
            c ==
                (
                    T == LexerType::Environment ?
                        '"' :
                        '`'
                )
        )
        {
            if (state.StringLiteral)
            {
                // End of string literal
                Lexer::FlushToken(
                    source,
                    stream,
                    state,
                    Map
                );

                state.StringLiteral = false;
            } else
            {
                // Start of string literal
                FlushToken(
                    source,
                    stream,
                    state,
                    Map
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
        if (Character::IsWhitespace(c))
        {
            FlushToken(
                source,
                stream,
                state,
                Map
            );

            state.Column++;
            continue;
        }

        // Detect identifiers
        if (state.Len == 0 && Character::IsIdentifier(c))
        {
            state.Identifier = true;
        }
        else if (
            c ==
                (
                    T == LexerType::Environment ?
                        '=' :
                        '@'
                )
        )
        {
            // Flush previous token
            FlushToken(
                source,
                stream,
                state,
                Map
            );

            // Add equal token
            state.Start = i;
            state.Len = 1;
            FlushToken(
                source,
                stream,
                state,
                Map
            );

            continue;
        }
        else if (
            (state.Identifier && !Character::IsIdentifier(c)) ||
            !state.Identifier
        )
        {
            throw AgnosticException<Token>(state);
        }

        state.Len++;
        state.Column++;
    }

    // Must not be inside a string literal at the end of the source
    if (state.StringLiteral)
    {
        throw AgnosticException<Token>(state);
    }

    // Flush any pending token
    FlushToken(
        source,
        stream,
        state,
        Map
    );

    return stream;
}

template
Lexer::ConditionalStream<Lexer::LexerType::Environment> Lexer::Tokenize<Lexer::LexerType::Environment>(
    Celery::Str::String &
);

template
Lexer::ConditionalStream<Lexer::LexerType::Core> Lexer::Tokenize<Lexer::LexerType::Core>(
    Celery::Str::String &
);
