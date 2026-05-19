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

#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::ArithmeticBase(
    TokenStreamView &input,
    ADT::Lang::TokenType delimiter
)
{
    auto lhs = ArithmeticLHS(input);

    // Syntax:
    // <Add/Sub/Mul/Div> <Num> <To/By> <Identifier>
    Expect(input, delimiter);

    auto &name = input.Peek();
    Expect(input, ADT::Lang::TokenType::Identifier);

    // Create the AST and return it
    auto ast = AllocateBase(name, ADT::Lang::ASTType::Add);
    ast->children.PushBack(AllocateBase(name, ADT::Lang::ASTType::Identifier));
    ast->children.PushBack(lhs);

    return ast;
}
