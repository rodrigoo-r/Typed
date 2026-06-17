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

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::TrimLeft(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    const char *ptr = str.data();
    size_t size = str.size();
    size_t start = 0;

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
                std::string_view{}
            };
        }

        return obj;
    }

    // If the string is a view, return a view
    if (obj.type == ADT::Runtime::ObjectType::String)
    {
        return {
            ADT::Runtime::ObjectType::String,
            std::string_view(ptr + start, size - start)
        };
    }

    // Otherwise, return an owned string
    return {
        ADT::Runtime::ObjectType::String,
        std::string_view(ptr + start, size - start)
    };
}