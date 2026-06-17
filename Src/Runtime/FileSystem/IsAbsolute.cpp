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

#include "IsAbsolute.h"

#include <filesystem>

#include "Support/Path/Join.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::IsAbsolute(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto str = Support::Runtime::AccessString(args[0]);
    auto path_str = Support::Runtime::ConvertToString(str);
    auto path = std::filesystem::path(path_str);

    return {
        ADT::Runtime::ObjectType::Boolean,
        path.is_absolute()
    };
}
