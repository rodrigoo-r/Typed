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

#include "IsRelative.h"

#include <filesystem>

#include "Support/Path/Join.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::IsRelative(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto str = Support::Runtime::AccessString(args[0]);
    auto path_str = Support::Runtime::ConvertToString(str);
    std::string std_path{path_str.Ptr(), path_str.Size()};
    auto path = std::filesystem::path(std_path);

    return {
        ADT::Runtime::ObjectType::Boolean,
        path.is_relative()
    };
}
