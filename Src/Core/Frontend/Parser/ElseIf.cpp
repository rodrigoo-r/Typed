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
    if (
        parent->type != ADT::Lang::ASTType::If &&
        parent->type != ADT::Lang::ASTType::ElseIf &&
        parent->type != ADT::Lang::ASTType::ConditionGroup
    )
    {
        throw ADT::Exception::UnexpectedToken(
            parent->line,
            parent->column
        );
    }

    if (parent->children.Back()->type != ADT::Lang::ASTType::ConditionGroup)
    {
        auto group = Allocate(ADT::Lang::ASTType::ConditionGroup);
        group->children.PushBack(parent->children.Back());
        parent->children.Back() = group;
    }

    If(parent->children.Back(), body_queue);
}
