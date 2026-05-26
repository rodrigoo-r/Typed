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
#include "Contains.h"

#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Contains(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    auto &target_obj = args[1];
    auto target = Support::Runtime::AccessString(target_obj);
    auto str = Support::Runtime::AccessString(obj);
    Celery::Trait::VeryLarge matched_chars = 0;
    auto max_count = target.Size();

    // Edge case: if both are empty
    if (target.Empty() && str.Empty())
    {
        return {
            ADT::Runtime::ObjectType::Boolean,
            true
        };
    }

    // Edge case: if one is empty and the other isn't
    if (target.Empty() || str.Empty())
    {
        return {
            ADT::Runtime::ObjectType::Boolean,
            false
        };
    }

    // Match characters
    for (auto i = 0; i < str.Size(); i++)
    {
        auto c = target[matched_chars];
        auto look = str[i];

        if (c == look)
        {
            matched_chars++;
        } else
        {
            // Reset the counter
            matched_chars = 0;
        }

        // Break early if the matched chars are met
        if (matched_chars == max_count)
        {
            break;
        }
    }

    return {
        ADT::Runtime::ObjectType::Boolean,
        matched_chars == max_count
    };
}