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

void Machine::Declare(TreePtr parent)
{
    // Syntax:
    // Declare <Identifier> As <Type> With <Expression>
    auto decl = Allocate(ADT::Lang::ASTType::Declare);    // Consume the Declare token
    parent->children.PushBack(decl);

    auto &name = tokens.Peek();
    Expect(ADT::Lang::TokenType::Identifier);
    Expect(ADT::Lang::TokenType::As);

    auto type = Type();

    // Build the AST structure
    decl->children.PushBack(AllocateBase(name, ADT::Lang::ASTType::Identifier));
    decl->children.PushBack(type);

    // Allow variables with no initial value
    if (tokens.Peek().type == ADT::Lang::TokenType::With)
    {
        Expect(ADT::Lang::TokenType::With);
        Expression(decl);
    } else
    {
        Expect(ADT::Lang::TokenType::Semicolon);
    }
}
