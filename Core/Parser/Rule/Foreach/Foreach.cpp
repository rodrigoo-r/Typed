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

#include "Core/Parser/Rule/Block/Block.h"
#include "Foreach.h"

#include "Core/Parser/Util/AllocateFrom.h"
#include "Core/Parser/Util/SafePeek.h"
#include "Shared/Stream/Expect.h"

using namespace Typed::Core;

void Parser::Rule::Foreach(
    AST *root,
    Lexer::TokenStream &stream,
    Queue::Block &queue
)
{
    Shared::Stream::Expect(stream, Lexer::Token::Type::StringLiteral);

    auto foreach = Util::AllocateFrom(
        stream,
        AST::Rule::Foreach
    );
    root->Children.PushBack(foreach);

    auto iden = Util::AllocateFrom(
        stream,
        AST::Rule::Identifier
    );
    foreach->Children.PushBack(iden);

    Shared::Stream::Expect(stream, Lexer::Token::Type::In);
    Shared::Stream::Expect(stream, Lexer::Token::Type::Identifier);

    auto source = Util::AllocateFrom(
        stream,
        AST::Rule::Identifier
    );
    foreach->Children.PushBack(source);

    // Create a new block for the foreach body
    auto body = Util::AllocateFrom(
        stream,
        AST::Rule::Block
    );
    foreach->Children.PushBack(body);
    queue.PushBack(body);
}
