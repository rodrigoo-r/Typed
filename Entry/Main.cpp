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

#include <Celery/Io/Io.h>

#include "Core/Parser/Parser.h"
#include "Environment/Env.h"
#include "Environment/Read.h"
#include "Runtime/Engine/Run.h"
#include "Runtime/Unit/Get.h"
#include "Shared/Lexer/Lexer.h"

using namespace Typed;

int main(const int argc, const char **argv)
{
    if (argc < 2)
    {
        Celery::Io::Println("Usage: printed <source.zt>");
        return 1;
    }

    // Parse the environment file
    auto env_file = Environment::Read();
    auto env_tokens = Typed::Shared::Lexer::Tokenize<
        Shared::Lexer::LexerType::Environment
    >(env_file);
    auto env = Environment::ParseEnv(env_tokens);

    // Parse the source file
    auto source = Celery::File::Read(argv[1]);
    auto tokens = Typed::Shared::Lexer::Tokenize<
        Shared::Lexer::LexerType::Core
    >(source);
    const auto ast = Core::Parser::Parse(tokens);
    auto unit = Runtime::Unit::Get(ast);

    // Run the unit
    Runtime::Engine::Run(unit, env);
    return 0;
}