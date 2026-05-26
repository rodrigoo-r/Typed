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

    auto str = Support::Runtime::AccessString(obj);
    auto target = Support::Runtime::AccessString(target_obj);
    auto max_matches = Support::Runtime::GetIntObj(max_match_obj);

    auto result = ADT::List::DynamicObject::Make();

    if (str.Empty() || target.Empty())
    {
        return {
            ADT::Runtime::ObjectType::List,
            result
        };
    }

    for (size_t i = 0; i + target.Size() <= str.Size(); ++i)
    {
        bool matched = true;

        for (size_t j = 0; j < target.Size(); ++j)
        {
            if (str[i + j] != target[j])
            {
                matched = false;
                break;
            }
        }

        if (matched)
        {
            result->EmplaceBack(
                ADT::Runtime::ObjectType::Integer,
                static_cast<int>(i)
            );

            if (max_matches > 0 &&
                result->Size() >= static_cast<size_t>(max_matches))
            {
                break;
            }

            // Skip over the matched substring to avoid overlaps
            i += target.Size() - 1;
        }
    }

    return {
        ADT::Runtime::ObjectType::List,
        result
    };
}