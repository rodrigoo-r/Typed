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
// Created by Rodrigo on 5/29/26.
//

#include "JoinPath.h"

#include <filesystem>

#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"
#include "Support/Runtime/TypeChecker.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::JoinPath(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto &list = Support::Runtime::GetListObj(obj);

    if (list->Empty()) return {
        ADT::Runtime::ObjectType::String,
        Celery::Str::External{"", 0}
    };

    std::filesystem::path path;

    // Build the path iteratively
    for (auto &elem : *list)
    {
        Support::Runtime::TypeCheck(
            ADT::Runtime::ObjectType::String,
            list->Front().type,
            trace->line,
            trace->column
        );

        if (elem.type == ADT::Runtime::ObjectType::String)
        {
            auto &str = Support::Runtime::GetStrObj(elem);
            Celery::Str::String owned{str.Ptr(), str.Size()};

            path /= owned.CStr();
        } else
        {
            auto &str = Support::Runtime::GetOwnedStrObj(elem);
            path /= str.CStr();
        }
    }

    auto result_str = path.string();
    return {
        ADT::Runtime::ObjectType::String,
        Celery::Str::String{result_str.data(), result_str.size()}
    };
}
