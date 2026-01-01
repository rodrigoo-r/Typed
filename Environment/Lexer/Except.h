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

#include "Shared/Trace.h"
#include "State.h"

namespace Typed::Environment::Lexer
{
    class Exception :
        public Global::Trace,
        public Celery::Except::Exception
    {
    public:
        Exception(const State &st) :
            Trace(st.Line, st.Column),
            Celery::Except::Exception("")
        {}
    };
}