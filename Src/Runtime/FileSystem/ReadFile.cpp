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

#include "ReadFile.h"

#include <fstream>

#include "ADT/Exception/CouldNotOpenFile.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::ReadFile(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &path_obj = args[0];
    auto ext = Support::Runtime::AccessString(path_obj);
    auto path = Support::Runtime::ConvertToString(ext);

    std::ifstream file(path.CStr());

    if (!file.is_open())
    {
        throw ADT::Exception::CouldNotOpenFile(
            trace->line,
            trace->column
        );
    }

    // Read the file
    std::string content(
        (std::istreambuf_iterator(file)),
        std::istreambuf_iterator<char>()
    );

    // Convert to Celery string
    Celery::Str::String result(content.data(), content.size());

    // Close the file
    file.close();

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}
