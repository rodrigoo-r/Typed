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

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Use()
{
    // We assume the Use token has been already consumed
    Expect(ADT::Lang::TokenType::Identifier);

    auto &token = tokens.Next();

    // The token's value will be put to the AST, so we
    // don't have to nest an Identifier AST under the Use AST
    auto node = AllocateBase(token, ADT::Lang::ASTType::Use);

    root->children.PushBack(node);
}
