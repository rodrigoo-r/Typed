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
// Created by Rodrigo on 5/24/26.
//

#include "ADT/List/Object.h"
#include "Access.h"

#include "ADT/Exception/OutOfBounds.h"
#include "Support/Runtime/NormalizeObject.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Lists;

ADT::Runtime::Object Lists::Access(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &list = Support::Runtime::GetListObj(args[0]);
    auto &idx = Support::Runtime::GetIntObj(args[1]);

    if (idx >= list->Size())
    {
        throw ADT::Exception::OutOfBounds(
            trace->line,
            trace->column
        );
    }

    return Support::Runtime::NormalizeObject(
        (*list)[idx],
        trace
    );
}