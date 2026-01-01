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
#include "Embed.h"

#include "Core/Parser/Util/AllocateFrom.h"
#include "Core/Parser/Util/SafePeek.h"
#include "Shared/Stream/Expect.h"

using namespace Typed::Core;

void Parser::Rule::Embed(
    AST *root,
    Lexer::TokenStream &stream
)
{
    Shared::Stream::Expect(stream, Lexer::Token::Type::Text);
    Shared::Stream::Expect(stream, Lexer::Token::Type::StringLiteral);

    auto embed = Util::AllocateFrom(
        stream,
        AST::Rule::Embed
    );
    root->Children.PushBack(embed);

    auto str = Util::AllocateFrom(
        stream,
        AST::Rule::StringLiteral
    );
    embed->Children.PushBack(str);

    // Peek to see if we have pushes
    auto &peek = Util::SafePeek(stream);
    while (peek.Kind == Lexer::Token::Type::Push)
    {
        // Consume the push token
        stream.Next();

        Shared::Stream::Expect(stream, Lexer::Token::Type::Identifier);
        peek = Util::SafePeek(stream);

        // Allocate the push AST node
        auto push = Util::AllocateFrom(
            stream,
            AST::Rule::Push
        );
        embed->Children.PushBack(push);
    }

    Shared::Stream::Expect(stream, Lexer::Token::Type::End);
}
