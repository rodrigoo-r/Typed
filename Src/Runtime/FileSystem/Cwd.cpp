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

#include "Cwd.h"

#include <filesystem>

#include "ADT/Exception/CouldNotOpenFile.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::Cwd(
    ADT::List::Object &_,
    ADT::Lang::AST *__
)
{
    auto cwd = std::filesystem::current_path();;
    auto str = cwd.string();

    return {
        ADT::Runtime::ObjectType::String,
        std::string(
            str.data(),
            str.size()
        )
    };

}
