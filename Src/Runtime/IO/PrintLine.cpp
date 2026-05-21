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

#include "PrintLine.h"

#include "Print.h"
#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::IO;

ADT::Runtime::Object IO::PrintLine(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    Print(args, trace);
    Celery::Io::Println();

    return {};
}