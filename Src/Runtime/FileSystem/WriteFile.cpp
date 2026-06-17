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
// Created by Rodrigo on 6/16/26.
//

#include "WriteFile.h"

#include <fstream>

#include "ADT/Exception/CouldNotOpenFile.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::WriteFile(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &path_obj = args[0];
    auto ext = Support::Runtime::AccessString(path_obj);
    auto path = Support::Runtime::ConvertToString(ext);
    auto content = Support::Runtime::AccessString(args[1]);
    auto content_str = Support::Runtime::ConvertToString(content);

    std::ofstream file(path.CStr());

    if (!file.is_open())
    {
        throw ADT::Exception::CouldNotOpenFile(
            trace->line,
            trace->column
        );
    }

    // Read the file
    std::string std_content(
        content_str.Ptr(),
        content_str.Size()
    );

    // Write to the file
    file << std_content;

    // Close the file
    file.close();

    return {};
}
