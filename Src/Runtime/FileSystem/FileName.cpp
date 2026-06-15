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

#include "FileName.h"

#include <filesystem>

#include "ADT/Exception/CouldNotCreateDirectory.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::FileName(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &path_obj = args[0];
    auto path_ext = Support::Runtime::AccessString(path_obj);
    auto path_str = Support::Runtime::ConvertToString(path_ext);

    auto path = std::filesystem::path(path_str.CStr());
    auto res = path.filename();
    auto res_str = res.string();

    return {
        ADT::Runtime::ObjectType::String,
        Celery::Str::String(res_str.data(), res_str.size())
    };
}
