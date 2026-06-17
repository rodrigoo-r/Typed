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
// Created by Rodrigo on 5/27/26.
//

#include "FileExists.h"

#include <filesystem>

#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::FileExists(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    auto path = Support::Runtime::ConvertToString(str);
    std::string std_path{path.Ptr(), path.Size()};

    return {
        ADT::Runtime::ObjectType::Boolean,
        std::filesystem::exists(std_path)
    };
}
