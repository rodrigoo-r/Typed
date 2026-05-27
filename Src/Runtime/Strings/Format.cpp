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

#include "Format.h"
#include "ADT/List/Object.h"
#include "Support/Format/Format.h"

#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Format(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    Celery::Str::String result;

    Support::Format::Format(
        str,
        args,
        result,
        trace->line,
        trace->column
    );

    return {
        ADT::Runtime::ObjectType::OwnedString,
        std::move(result)
    };
}