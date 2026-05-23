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
    auto last = ConditionGroup(parent, body_queue);

    auto ast = AllocateBase(
        tokens.Peek(),
        ADT::Lang::ASTType::Else
    );

    auto body = AllocateBase(
        tokens.Peek(),
        ADT::Lang::ASTType::Body
    );

    Expect(ADT::Lang::TokenType::Begin);
    last->children.PushBack(ast);
    ast->children.PushBack(body);

    // Add the body to the queue
    body_queue.emplace_front(
        body,
        else_token
    );
}
