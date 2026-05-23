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
// Created by Rodrigo on 5/21/26.
//

#include "ADT/Exception/UnexpectedReturn.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

ADT::Runtime::Object Walker::Return(
    ProcedureRef procedure,
    VariableStack &stack,
    TreePtr body
)
{
    // Make sure the procedure is allowed to return
    if (procedure.return_type == ADT::Runtime::ObjectType::Void)
    {
        throw ADT::Exception::UnexpectedReturn(
            body->line,
            body->column
        );
    }

    return Expression(stack, body->children[0]);
}