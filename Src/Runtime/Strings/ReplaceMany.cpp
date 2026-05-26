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
    ADT::Lang::AST *_
)
{
    ADT::List::Object find_indexes_arg;
    find_indexes_arg.EmplaceBack(args[0]);
    find_indexes_arg.EmplaceBack(args[3]);

    auto res = FindIndexes(find_indexes_arg, _);
    auto &obj = args[0];
    auto &target_obj = args[1];
    auto &replacing_obj = args[2];
    auto str = Support::Runtime::AccessString(obj);
    auto replacing = Support::Runtime::AccessString(replacing_obj);
    auto target = Support::Runtime::AccessString(target_obj);
    auto &indexes = Support::Runtime::GetListObj(res);
    auto last_replaced_idx = 0;

    Celery::Str::String result;
    result.Resize(
        str.Size()
        - (replacing.Size() * indexes->Size())
        + (target.Size() * indexes->Size())
    );

    for (auto &idx_obj : *indexes)
    {
        auto &idx = Support::Runtime::GetIntObj(idx_obj);

        // If not found, exit early
        if (idx == -1) return obj;

        // Write everything before the index
        result.Write(
            str.Ptr() + last_replaced_idx,
            idx - last_replaced_idx
        );

        // Write the replaced index
        result.Write(
            target.Ptr(),
            target.Size()
        );

        last_replaced_idx = idx + replacing.Size();
    }

    return {
        ADT::Runtime::ObjectType::OwnedString,
        std::move(result)
    };
}