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

#include "Support/Path/Join.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::JoinPath(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto path = Support::Path::Join(args, trace);

    auto result_str = path.string();
    return {
        ADT::Runtime::ObjectType::String,
        Celery::Str::String{result_str.data(), result_str.size()}
    };
}
