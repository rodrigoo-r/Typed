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

#include "CreateFile.h"

#include <fstream>

#include "ADT/Exception/CouldNotOpenFile.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::FileSystem;

ADT::Runtime::Object FileSystem::CreateFile(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &path_obj = args[0];
    auto path_ext = Support::Runtime::AccessString(path_obj);
    auto path = Support::Runtime::ConvertToString(path_ext);

    std::ofstream my_file(path.CStr());
    if (my_file.is_open())
    {
        my_file.close();
        return {};
    }

    throw ADT::Exception::CouldNotOpenFile(
        trace->line,
        trace->column
    );
}
