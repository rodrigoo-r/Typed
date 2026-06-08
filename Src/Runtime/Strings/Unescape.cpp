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
// Created by Rodrigo on 6/1/26.
//

#include "Unescape.h"
#include "ADT/List/Object.h"
#include "Support/Strconv/Unescape.h"

#include <charconv>

#include "ADT/Exception/UnknownFormat.h"
#include "ADT/Lang/AST.h"
#include "ADT/Stream/External.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Unescape(
    ADT::Runtime::Object &obj,
    ADT::Lang::AST *trace
)
{
    auto str = Support::Runtime::AccessString(obj);

    return {
        ADT::Runtime::ObjectType::String,
        Support::Strconv::Unescape(str, trace)
    };
}

ADT::Runtime::Object Strings::Unescape(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    return Unescape(args[0], trace);
}