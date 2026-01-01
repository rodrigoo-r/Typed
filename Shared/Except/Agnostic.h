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
#include <Celery/Except/Base.h>

#include "../Lexer/State.h"
#include "../Stream/TokenStream.h"
#include "Shared/Trace.h"

namespace Typed::Shared
{
    template <typename Value>
    class AgnosticException :
        public Global::Trace,
        public Celery::Except::Exception
    {
    public:
        AgnosticException(const LexerState &st) :
            Trace(st.Line, st.Column),
            Celery::Except::Exception("")
        {}

        AgnosticException(TokenStream<Value> &stream) :
            Trace(
                1,
                1
            ),
            Celery::Except::Exception("")
        {
            if (stream.Pos() > 0)
            {
                const auto &token = stream.Curr();
                this->Line = token.Line;
                this->Column = token.Column;
            }
        }
    };
}