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

#include "Parser.h"
#include "Support/Stream/SafeNext.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Else(
    TreePtr parent,
    BodyQueue &body_queue
)
{
    auto &else_token = Support::Stream::SafeNext(tokens);
    auto last = ConditionGroup(parent, body_queue);

    auto ast = AllocateBase(
        Support::Stream::SafePeek(tokens),
        ADT::Lang::ASTType::Else
    );

    auto body = AllocateBase(
        Support::Stream::SafePeek(tokens),
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
