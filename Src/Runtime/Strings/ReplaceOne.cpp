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
#include "ReplaceOne.h"

#include "FindIndex.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::ReplaceOne(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto res = FindIndex(args, _);
    auto &obj = args[0];
    auto &target_obj = args[1];
    auto &replacing_obj = args[2];
    auto str = Support::Runtime::AccessString(obj);
    auto replacing = Support::Runtime::AccessString(replacing_obj);
    auto target = Support::Runtime::AccessString(target_obj);
    auto &idx = Support::Runtime::GetIntObj(res);

    // If not found, exit early
    if (idx == -1) return obj;

    Celery::Str::String result;
    result.Resize(str.Size() - replacing.Size() + target.Size());

    // Write the first part of the string
    result.Write(str.Ptr(), idx);
    // Write the target
    result.Write(target.Ptr(), target.Size());
    // Write the remaining part
    result.Write(
        str.Ptr() + idx + target.Size(),
        str.Size() - replacing.Size() - idx
    );

    return {
        ADT::Runtime::ObjectType::OwnedString,
        std::move(result)
    };
}