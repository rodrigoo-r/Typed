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

#include "Env.h"

#include "Shared/Expect.h"

using namespace Typed::Environment;

Env Typed::Environment::ParseEnv(Lexer::TokenStream &stream)
{
    Env env;

    // Iterate through the token stream and populate the env map
    while (stream.HasNext())
    {
        Shared::Expect(
            stream,
            Lexer::Token::Type::Identifier
        );

        auto key = stream.Curr();
        Shared::Expect(
            stream,
            Lexer::Token::Type::Equal
        );
        Shared::Expect(
            stream,
            Lexer::Token::Type::StringLiteral
        );

        auto value = stream.Curr();

        // Insert into the env map
        env.emplace(
            key.value,
            value.value
        );
    }

    return env;
}
