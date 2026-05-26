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
// Created by Rodrigo on 5/26/26.
//

#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"
#include "FindIndexes.h"

#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::FindIndexes(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    auto &target_obj = args[1];
    auto &max_match_obj = args[2];
    auto target = Support::Runtime::AccessString(target_obj);
    auto str = Support::Runtime::AccessString(obj);
    auto max_matches = Support::Runtime::GetIntObj(max_match_obj);
    Celery::Trait::VeryLarge matched_chars = 0;
    auto max_count = target.Size();
    int start = 0;
    auto result = ADT::List::DynamicObject::Make();

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
            start = -1;
        }

        // Update the start index if we matched 1 character
        if (matched_chars == 1)
        {
            start = i;
        }

        // Break early if the matched chars are met
        if (matched_chars == max_count)
        {
            result->EmplaceBack(
                ADT::Runtime::ObjectType::Integer,
                start
            );

            // Reset the count
            start = 0;

            // Break when we find the maximum matches
            if (max_matches == result->Size())
            {
                break;
            }
        }
    }

    return {
        ADT::Runtime::ObjectType::List,
        result
    };
}