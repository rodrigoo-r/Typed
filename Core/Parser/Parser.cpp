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

#include "Parser.h"

#include "Rule/Procedure/Procedure.h"
#include "Shared/Except/Agnostic.h"
#include "Util/AllocateFrom.h"

using namespace Typed::Core;

Parser::AST* Parser::Parse(Lexer::TokenStream &stream)
{
    auto root = Util::AllocateFrom(stream, AST::Rule::Root);

    while (stream.HasNext())
    {
        auto &curr = stream.Next();

        switch (curr.Kind)
        {
            case Lexer::Token::Type::Procedure:
            {
                Rule::Procedure(root, stream);
                break;
            }

            default:
            {
                throw Shared::AgnosticException(stream);
            }
        }
    }

    return root;
}
