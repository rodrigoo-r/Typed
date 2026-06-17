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

#include "Parser.h"
#include "Support/Equality/TokenType.h"
#include "Support/Stream/Extract.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::If(
    TreePtr parent,
    BodyQueue &body_queue
)
{
    auto &if_token = Support::Stream::SafeNext(tokens);
    auto ast = AllocateBase(
        Support::Stream::SafePeek(tokens),
        ADT::Lang::ASTType::If
    );
    auto body = AllocateBase(
        Support::Stream::SafePeek(tokens),
        ADT::Lang::ASTType::Body
    );

    auto condition_stream = Support::Stream::Extract<
        ADT::Lang::Token,
        Support::Equality::TokenType
    >(tokens, ADT::Lang::TokenType::Then);

    parent->children.push_back(ast);
    Expect(ADT::Lang::TokenType::Begin);

    // Parse the expression
    Expression(ast, condition_stream);
    ast->children.push_back(body);

    // Add the body to the queue
    body_queue.emplace_front(
        body,
        if_token
    );
}
