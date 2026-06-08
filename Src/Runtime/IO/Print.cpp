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

#include "ADT/Exception/MismatchedArgCount.h"
#include "ADT/Stdout/Wrapper.h"
#include "Support/Format/Format.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::IO;

inline ADT::Stdout::Wrapper out;

ADT::Runtime::Object IO::Print(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto fmt = Support::Runtime::AccessString(obj);

    Support::Format::Format(
        fmt,
        args,
        out,
        trace
    );

    return {};
}
