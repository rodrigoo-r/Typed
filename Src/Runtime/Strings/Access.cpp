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
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Access(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    auto &idx = Support::Runtime::GetIntObj(args[1]);
    const char *ptr = str.data();
    size_t size = str.size();

    // Make sure that the index is within bounds
    if (idx >= size)
    {
        throw ADT::Exception::OutOfBounds(
            trace->line,
            trace->column
        );
    }

    // Return an owned string if the original is owned
    if (
        std::holds_alternative<std::string>(obj.value)
    )
    {
        return {
            ADT::Runtime::ObjectType::String,
            std::string(
                ptr + idx,
                1
            )
        };
    }

    // Otherwise, return a view
    return {
        ADT::Runtime::ObjectType::String,
        std::string_view(
            ptr + idx,
            1
        )
    };
}