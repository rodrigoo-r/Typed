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
// Created by Rodrigo on 5/23/26.
//

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::ElseIf(
    TreePtr parent,
    BodyQueue &body_queue
)
{
    // Make sure the last child is an If child
    if (parent->type != ADT::Lang::ASTType::If)
    {
        throw ADT::Exception::UnexpectedToken(
            parent->line,
            parent->column
        );
    }

    If(parent, body_queue);
    parent->children.Back()->type = ADT::Lang::ASTType::ElseIf;
}
