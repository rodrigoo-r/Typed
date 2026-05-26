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
#include "TrimRight.h"

#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::TrimRight(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    char *ptr = str.Ptr();
    Celery::Trait::VeryLarge size = str.Size();
    Celery::Trait::VeryLarge end = size - 1;

    // Remove all empty characters
    while (
        end > 0 &&
        (
            ptr[end] == ' ' ||
            ptr[end] == '\t' ||
            ptr[end] == '\n' ||
            ptr[end] == '\r'
        )
    )
    {
        --end;
    }

    // Edge case: the string is empty
    if (end == 0)
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
            Celery::Str::External(ptr, end + 1)
        };
    }

    // Otherwise, return an owned string
    return {
        ADT::Runtime::ObjectType::OwnedString,
        Celery::Str::String(ptr, end + 1)
    };
}