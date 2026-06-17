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
// Created by Rodrigo on 6/15/26.
//

#include "ScanDirectory.h"

#include <filesystem>

#include "ADT/Exception/CouldNotCreateDirectory.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::ScanDirectory(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &path_obj = args[0];
    auto path_ext = Support::Runtime::AccessString(path_obj);
    auto path = Support::Runtime::ConvertToString(path_ext);

    std::string path_str{path.Ptr(), path.Size()};
    auto res = std::filesystem::directory_iterator(path_str);
    auto res_list = ADT::List::DynamicObject::Make();

    for (auto &entry : res)
    {
        auto &entry_path = entry.path();
        auto entry_path_str = entry_path.string();
        Celery::Str::String entry_path_obj;

        entry_path_obj.Resize(entry_path_str.size());
        entry_path_obj.Write(entry_path_str.data(), entry_path_str.size());
        res_list->PushBack({
            ADT::Runtime::ObjectType::String,
            std::move(entry_path_obj)
        });
    }

    return {
        ADT::Runtime::ObjectType::List,
        res_list
    };
}
