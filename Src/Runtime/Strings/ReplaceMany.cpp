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
#include "ReplaceMany.h"

#include "FindIndex.h"
#include "FindIndexes.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::ReplaceMany(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    ADT::List::Object find_indexes_arg;
    find_indexes_arg.EmplaceBack(args[0]);
    find_indexes_arg.EmplaceBack(args[1]);
    find_indexes_arg.EmplaceBack(args[3]);

    auto res = FindIndexes(find_indexes_arg, trace);

    auto &obj = args[0];
    auto &find_obj = args[1];
    auto &replacement_obj = args[2];

    auto str = Support::Runtime::AccessString(obj);
    auto find = Support::Runtime::AccessString(find_obj);
    auto replacement = Support::Runtime::AccessString(replacement_obj);

    auto &indexes = Support::Runtime::GetListObj(res);

    // Nothing to replace
    if (indexes->Empty())
    {
        return obj;
    }

    Celery::Str::String result;

    result.Resize(
        str.Size()
        - (find.Size() * indexes->Size())
        + (replacement.Size() * indexes->Size())
    );

    Celery::Trait::VeryLarge last_pos = 0;

    for (auto &idx_obj : *indexes)
    {
        auto idx = Support::Runtime::GetIntObj(idx_obj);

        // Copy text before the match
        result.Write(
            str.Ptr() + last_pos,
            idx - last_pos
        );

        // Copy replacement text
        result.Write(
            replacement.Ptr(),
            replacement.Size()
        );

        // Skip over the matched text
        last_pos = idx + find.Size();
    }

    // Copy remaining tail
    result.Write(
        str.Ptr() + last_pos,
        str.Size() - last_pos
    );

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}