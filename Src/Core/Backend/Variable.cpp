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
// Created by Rodrigo on 5/22/26.
//

#include "ADT/Exception/UnknownSymbol.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

ADT::Runtime::Object Walker::Variable(
    VariableMap &stack,
    TreePtr body
)
{
    // Try to find the variable
    auto it = stack.find(body->value);
    if (it == stack.end())
    {
        throw ADT::Exception::UnknownSymbol(
            body->line,
            body->column
        );
    }

    return it->second;
}
