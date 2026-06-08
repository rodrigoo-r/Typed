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
#include "Set.h"

#include "ADT/Exception/MismatchedType.h"
#include "ADT/Exception/OutOfBounds.h"
#include "Support/Runtime/NormalizeObject.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Lists;

ADT::Runtime::Object Lists::Set(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &list = Support::Runtime::GetListObj(args[0]);
    auto &idx = Support::Runtime::GetIntObj(args[1]);
    auto obj = Support::Runtime::NormalizeObject(args[2], trace);

    // Make sure the element is within bounds
    if (idx >= list->Size())
    {
        throw ADT::Exception::OutOfBounds(
            trace->line,
            trace->column
        );
    }

    // Make sure the object isn't void
    if (
        obj.type == ADT::Runtime::ObjectType::Void ||
        obj.type == ADT::Runtime::ObjectType::Any
    )
    {
        throw ADT::Exception::MismatchedType(
            trace->line,
            trace->column
        );
    }

    // Set the element directly
    (*list)[idx] = obj;
    return {};
}