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
#include "Support/Equality/TokenType.h"
#include "Support/Stream/Extract.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::For(TreePtr parent, BodyQueue &body_queue)
{
    auto &for_token = Support::Stream::SafePeek(tokens);
    auto ast = Allocate(ADT::Lang::ASTType::For);
    parent->children.PushBack(ast);

    auto &var_name = Support::Stream::SafePeek(tokens);
    Expect(ADT::Lang::TokenType::Identifier);
    Expect(ADT::Lang::TokenType::As);
    auto type = Type();

    Expect(ADT::Lang::TokenType::In);
    auto from = Support::Stream::Extract<
        ADT::Lang::Token,
        Support::Equality::TokenType
    >(tokens, ADT::Lang::TokenType::To);

    auto to = Support::Stream::Extract<
        ADT::Lang::Token,
        Support::Equality::TokenType
    >(tokens, ADT::Lang::TokenType::Step);

    auto step = Support::Stream::Extract<
        ADT::Lang::Token,
        Support::Equality::TokenType
    >(tokens, ADT::Lang::TokenType::Do);

    auto body = AllocateBase(for_token, ADT::Lang::ASTType::Body);

    Expect(ADT::Lang::TokenType::Begin);
    body_queue.emplace_front(body, for_token);

    auto decl = AllocateBase(var_name, ADT::Lang::ASTType::Declare);
    decl->children.PushBack(AllocateBase(var_name, ADT::Lang::ASTType::Identifier));
    decl->children.PushBack(type);

    ast->children.PushBack(decl);
    Expression(ast, from);
    Expression(ast, to);
    Expression(ast, step);
    ast->children.PushBack(body);
}
