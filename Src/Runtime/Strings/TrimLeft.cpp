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

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::TrimLeft(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    char *ptr = nullptr;
    Celery::Trait::VeryLarge size = 0;
    Celery::Trait::VeryLarge start = 0;

    if (obj.type == ADT::Runtime::ObjectType::String)
    {
        auto &str = Support::Runtime::GetStrObj(obj);
        ptr = str.Ptr();
        size = str.Size();
    } else
    {
        auto &str = Support::Runtime::GetOwnedStrObj(obj);
        ptr = str.Ptr();
        size = str.Size();
    }

    // Remove all empty characters
    while (
        start < size &&
        (
            ptr[start] == ' ' ||
            ptr[start] == '\t' ||
            ptr[start] == '\n' ||
            ptr[start] == '\r'
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
        ADT::Runtime::ObjectType::OwnedString,
        Celery::Str::String(ptr + start, size - start)
    };
}