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
// Created by Rodrigo on 5/24/26.
//

#include "ADT/List/Object.h"
#include "TrimRight.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::TrimRight(
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
        start = size - 1;
    } else
    {
        auto &str = Support::Runtime::GetOwnedStrObj(obj);
        ptr = str.Ptr();
        size = str.Size();
        start = size - 1;
    }

    // Remove all empty characters
    while (
        start > 0 &&
        (
            ptr[start] == ' ' ||
            ptr[start] == '\t' ||
            ptr[start] == '\n' ||
            ptr[start] == '\r'
        )
    )
    {
        --start;
    }

    // Edge case: the string is empty
    if (start == 0)
    {
        return {
            ADT::Runtime::ObjectType::String,
            Celery::Str::External("", 0)
        };
    }

    // If the string is a view, return a view
    if (obj.type == ADT::Runtime::ObjectType::String)
    {
        return {
            ADT::Runtime::ObjectType::String,
            Celery::Str::External(ptr, size - start)
        };
    }

    // Otherwise, return an owned string
    return {
        ADT::Runtime::ObjectType::OwnedString,
        Celery::Str::String(ptr, size - start)
    };
}