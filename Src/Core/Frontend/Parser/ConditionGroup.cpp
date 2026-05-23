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

Machine::TreePtr Machine::ConditionGroup(
    TreePtr parent,
    BodyQueue &body_queue
)
{
    body_queue.pop_front();
    if (body_queue.empty())
    {
        throw ADT::Exception::UnexpectedToken(
            parent->line,
            parent->column
        );
    }

    auto &parent_el = body_queue.front();
    auto &parent_body = parent_el.body;

    // Make sure the last child is an If child
    auto last = parent_body->children.Back();
    if (
        last->type != ADT::Lang::ASTType::If &&
        last->type != ADT::Lang::ASTType::ElseIf &&
        last->type != ADT::Lang::ASTType::ConditionGroup
    )
    {
        throw ADT::Exception::UnexpectedToken(
            parent->line,
            parent->column
        );
    }

    if (last->type != ADT::Lang::ASTType::ConditionGroup)
    {
        auto group = AllocateBase(
            tokens.Curr(),
            ADT::Lang::ASTType::ConditionGroup
        );

        group->children.PushBack(last);
        parent_body->children.Back() = group;
        last = group;
    }

    return last;
}
