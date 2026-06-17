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
// Created by Rodrigo on 5/18/26.
//

#include "Parser.h"
#include "Support/Stream/SafePeek.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Use()
{
    // We assume the Use token has been already consumed
    auto &identifier = Support::Stream::SafePeek(tokens);
    Expect(ADT::Lang::TokenType::Identifier);

    // The token's value will be put to the AST, so we
    // don't have to nest an Identifier AST under the Use AST
    auto node = AllocateBase(identifier, ADT::Lang::ASTType::Use);

    // Consume the semicolon
    Expect(ADT::Lang::TokenType::Semicolon);

    root->children.push_back(node);
}
