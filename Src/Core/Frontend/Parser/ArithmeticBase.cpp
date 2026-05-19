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
// Created by Rodrigo on 5/19/26.
//

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::ArithmeticBase(TokenStreamView &input)
{
    auto &num = input.Next();

    // Validate that the input is a number, float or identifier
    if (
        num.type != ADT::Lang::TokenType::NumberLiteral &&
        num.type != ADT::Lang::TokenType::FloatLiteral &&
        num.type != ADT::Lang::TokenType::Identifier
    )
    {
        throw ADT::Exception::UnexpectedToken(
            num.line,
            num.column
        );
    }

    auto lhs = AllocateBase(
        num,
        num.type == ADT::Lang::TokenType::NumberLiteral ?
            ADT::Lang::ASTType::NumberLiteral
        : num.type == ADT::Lang::TokenType::FloatLiteral ?
            ADT::Lang::ASTType::FloatLiteral
        : ADT::Lang::ASTType::Identifier
    );

    // Syntax:
    // <Add/Sub> <Num> <To> <Identifier>
    Expect(input, ADT::Lang::TokenType::To);

    auto &name = input.Peek();
    Expect(input, ADT::Lang::TokenType::Identifier);

    // Create the AST and return it
    auto ast = AllocateBase(num, ADT::Lang::ASTType::Add);
    ast->children.PushBack(AllocateBase(name, ADT::Lang::ASTType::Identifier));
    ast->children.PushBack(lhs);

    return ast;
}
