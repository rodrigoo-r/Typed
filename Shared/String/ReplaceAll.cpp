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

#include "ReplaceAll.h"

using namespace Typed::Shared;

void String::ReplaceAll(
    Celery::Str::String& handle,
    const Celery::Str::External &search_for,
    const Celery::Str::External &replace_with
)
{
    if (handle.Empty() || search_for.Empty())
        return;

    const char* src = handle.CStr();
    const auto src_len = handle.Len();
    const auto search_len = search_for.Size();

    Celery::Str::String result;
    result.EnsureGrowth(src_len); // rough lower bound

    Celery::Trait::VeryLarge i = 0;
    while (i < src_len)
    {
        // Check for match
        if (
            i + search_len <= src_len &&
            std::memcmp(
                src + i,
                search_for.Ptr(),
                search_len
            ) == 0
        )
        {
            // Write replacement
            result.Write(replace_with.Ptr(), replace_with.Size());
            i += search_len;
        }
        else
        {
            // Copy one char
            result.PushBack(src[i]);
            ++i;
        }
    }

    handle = std::move(result);
}