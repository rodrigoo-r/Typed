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
// Created by Rodrigo on 5/20/26.
//

#include "ReadLine.h"
#include <Celery/Io/Io.h>

#include "Print.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::IO;

ADT::Runtime::Object IO::ReadLine(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    // Flush the stdout buffer before reading
    Celery::Io::IStdout.Flush();

    // Read the line
    std::string line;
    std::getline(std::cin, line);

    // Copy the string
    Celery::Str::String str;
    str.Write(line.data(), line.size());

    return {
        ADT::Runtime::ObjectType::OwnedString,
        std::move(str)
    };
}