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

#include "CreateDirectory.h"

#include <filesystem>

#include "ADT/Exception/CouldNotCreateDirectory.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::CreateDirectory(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &path_obj = args[0];
    auto path_ext = Support::Runtime::AccessString(path_obj);
    auto path = Support::Runtime::ConvertToString(path_ext);

    auto res = std::filesystem::create_directories(path);
    if (!res)
    {
        throw ADT::Exception::CouldNotCreateDirectory(
            trace->line,
            trace->column
        );
    }

    return {};
}
