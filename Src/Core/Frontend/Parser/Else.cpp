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

void Machine::Else(
    TreePtr parent,
    BodyQueue &body_queue
)
{
    auto &else_token = tokens.Next();

    // Make sure the last child is an If child
    if (
        parent->type != ADT::Lang::ASTType::If &&
        parent->type != ADT::Lang::ASTType::ConditionGroup
    )
    {
        throw ADT::Exception::UnexpectedToken(
            parent->line,
            parent->column
        );
    }

    auto real_parent = parent->children.Back();
    if (real_parent->type != ADT::Lang::ASTType::ConditionGroup)
    {
        auto group = AllocateBase(
            tokens.Curr(),
            ADT::Lang::ASTType::ConditionGroup
        );

        group->children.PushBack(real_parent);
        parent->children.Back() = group;
        real_parent = group;
    }

    auto ast = AllocateBase(
        tokens.Peek(),
        ADT::Lang::ASTType::Else
    );

    auto body = AllocateBase(
        tokens.Peek(),
        ADT::Lang::ASTType::Body
    );

    Expect(ADT::Lang::TokenType::Begin);
    real_parent->children.PushBack(ast);
    ast->children.PushBack(body);

    // Add the body to the queue
    body_queue.emplace_front(
        body,
        else_token
    );
}
