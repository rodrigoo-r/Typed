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

#include "Procedure.h"

#include "Core/Parser/Util/AllocateFrom.h"
#include "Shared/Stream/Expect.h"

using namespace Typed::Core;

void Parser::Rule::Procedure(
    AST *root,
    Lexer::TokenStream &stream
)
{
    Shared::Stream::Expect(stream, Lexer::Token::Type::Identifier);

    auto proc = Util::AllocateFrom(
        stream,
        AST::Rule::Procedure
    );
    root->children.PushBack(proc);


}
