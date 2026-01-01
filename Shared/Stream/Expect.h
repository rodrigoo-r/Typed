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
#include <Celery/Io/Io.h>


#include "../Except/Agnostic.h"

namespace Typed::Shared::Stream
{
    template <typename Value>
    void Expect(
        TokenStream<Value> &stream,
        typename Value::Type expected_type
    )
    {
        if (!stream.HasNext())
        {
            throw AgnosticException<Value>{stream};
        }

        auto &token = stream.Next();
        if (token.Kind != expected_type)
        {
            throw AgnosticException<Value>{stream};
        }
    }
}