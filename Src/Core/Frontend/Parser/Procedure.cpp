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

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Procedure()
{
    // Expect the procedure's name
    auto &identifier = tokens.Peek();
    Expect(ADT::Lang::TokenType::Identifier);

    auto node = AllocateBase(identifier, ADT::Lang::ASTType::Procedure);
    root->children.PushBack(node);

    // Case: The procedure has arguments
    auto &peek = tokens.Peek();
    if (peek.type == ADT::Lang::TokenType::With)
    {
        auto args = Allocate(ADT::Lang::ASTType::Arguments);
        node->children.PushBack(args);

        Expect(ADT::Lang::TokenType::Arguments);
        tokens.Next();

        // Parse arguments
        while (peek.type != ADT::Lang::TokenType::Begin)
        {
            // Expect the argument's structure: <Identifier> As <Type>
            peek = tokens.Peek();
            Expect(ADT::Lang::TokenType::Identifier);
            Expect(ADT::Lang::TokenType::As);

            // Parse the type
            auto type = Type();

            // Build the AST
            auto arg = Allocate(ADT::Lang::ASTType::Argument);
            arg->children.PushBack(AllocateBase(peek, ADT::Lang::ASTType::Identifier));
            arg->children.PushBack(type);

            args->children.PushBack(arg);
            peek = tokens.Peek();
        }
    }

    if (peek.type != ADT::Lang::TokenType::Begin)
    {
        throw ADT::Exception::UnexpectedToken(
            peek.line,
            peek.column
        );
    }
}
