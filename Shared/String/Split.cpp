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

#include "Split.h"

using namespace Typed::Shared;

Celery::Array::Vector<Celery::Str::External> String::Split(
    Celery::Str::External &handle,
    const Celery::Str::External& delimiter
)
{
    Celery::Array::Vector<Celery::Str::External> result;

    if (handle.Empty())
        return result;

    if (delimiter.Empty()) {
        // whole string as one token
        result.EmplaceBack(handle);
        return result;
    }

    Celery::Trait::VeryLarge start = 0;
    auto len = handle.Size();
    auto dlen = delimiter.Size();

    // Optional rough pre-alloc
    result.EnsureGrowth(len / (dlen + 1) + 1);

    Celery::Trait::VeryLarge i = 0;
    while (i + dlen <= len)
    {
        if (
            std::memcmp(
                handle.Ptr() + i,
                delimiter.Ptr(), dlen
            ) == 0
        )
        {
            result.EmplaceBack(
                handle.Ptr() + start,
                i - start
            );
            i += dlen;
            start = i;
        }
        else
        {
            ++i;
        }
    }

    // Tail
    if (start <= len)
    {
        result.EmplaceBack(
            handle.Ptr() + start,
            len - start
        );
    }

    return result;
}
