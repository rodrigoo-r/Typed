/*
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #                           Typed                     # *
 * #                   A text formatting DSL             # *
 * #                                                     # *
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #         Created by Rodrigo R. & Contributors        # *
 * #         Released under the Apache License 2.0       # *
 * #            Check LICENSE.MD for more info           # *
 * #                                                     # *
 * #-----------------------------------------------------# *
*/

//
// Created by Rodrigo on 5/25/26.
//

#include "ADT/List/Object.h"
#include "TrimLeft.h"

#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/NormalizeObject.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::TrimLeft(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto obj = Support::Runtime::NormalizeObject(args[0], trace);
    auto str = Support::Runtime::AccessString(obj);
    char *ptr = str.Ptr();
    Celery::Trait::VeryLarge size = str.Size();
    Celery::Trait::VeryLarge start = 0;

    // Remove all empty characters
    while (
        start < size &&
        (
            std::isblank(ptr[start]) ||
            std::iswblank(ptr[start]) ||
            std::isspace(ptr[start]) ||
            std::iswspace(ptr[start]) ||
            std::iscntrl(ptr[start]) ||
            std::iswcntrl(ptr[start])
        )
    )
    {
        ++start;
    }

    // Edge case: the string is empty
    if (start == size)
    {
        if (start > 0)
        {
            return {
                ADT::Runtime::ObjectType::String,
                Celery::Str::External("", 0)
            };
        }

        return obj;
    }

    // If the string is a view, return a view
    if (obj.type == ADT::Runtime::ObjectType::String)
    {
        return {
            ADT::Runtime::ObjectType::String,
            Celery::Str::External(ptr + start, size - start)
        };
    }

    // Otherwise, return an owned string
    return {
        ADT::Runtime::ObjectType::String,
        Celery::Str::String(ptr + start, size - start)
    };
}