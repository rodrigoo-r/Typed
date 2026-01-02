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

#include "../Stream/TokenStream.h"
#include "AgnosticHandler.h"
#include "Core/Lexer/Token.h"
#include "Environment/Lexer/Token.h"

namespace Typed::Shared::Lexer
{
    enum class LexerType
    {
        Environment,
        Core
    };

    template <LexerType T>
    using ConditionalStream = Stream::TokenStream<
        std::conditional_t<
            T == LexerType::Environment,
            Environment::Lexer::Token,
            Core::Lexer::Token
        >
    >;

    template <LexerType T>
    using ConditionalToken = std::conditional_t<
        T == LexerType::Environment,
        Environment::Lexer::Token,
        Core::Lexer::Token
    >;

    template <
        LexerType T,
        Celery::Trait::VeryLarge PunctSize
    >
    ConditionalStream<T> Tokenize(
        Celery::Str::String &,
        AgnosticHandler<
            ConditionalToken<T>,
            PunctSize
        > &
    );
}