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

Celery::Array::Vector<Celery::Str::String> String::Split(
    Celery::Str::String& handle,
    const Celery::Str::External& delimiter
)
{
    Celery::Array::Vector<Celery::Str::String> result;

    if (handle.Empty())
        return result;

    if (delimiter.Empty())
    {
        // Degenerate case: whole string as one token
        result.EmplaceBack(handle);
        return result;
    }

    const char* src = handle.CStr();
    const auto len = handle.Len();
    const auto delim_len = delimiter.Size();

    Celery::Str::String current;

    size_t i = 0;
    while (i < len)
    {
        // Delimiter match?
        if (
            i + delim_len <= len &&
            std::memcmp(
                src + i,
                delimiter.Ptr(),
                delim_len
            ) == 0
        )
        {
            result.EmplaceBack(std::move(current));
            current.Reset(); // reuse buffer
            i += delim_len;
        }
        else
        {
            current.EmplaceBack(src[i]);
            ++i;
        }
    }

    // Push last segment (even if empty)
    result.EmplaceBack(std::move(current));

    return result;
}
