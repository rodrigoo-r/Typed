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

#include "Print.h"

#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::IO;

void IO::Print(ADT::List::Object &args)
{
    auto &fmt_obj = args[0];
    auto &fmt = std::get<Celery::Str::External>(fmt_obj.value);


    Celery::Io::Println(fmt);
}
