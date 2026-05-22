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

#include "Support/Stream/Expect.h"


#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::Greater(
    TokenStreamView &input,
    TreePtr op
)
{
    Expect(input, ADT::Lang::TokenType::Than);

    // Account for Greater Than Or Equal To
    auto &peek = input.Peek();
    if (peek.type == ADT::Lang::TokenType::Or)
    {
        op->type = ADT::Lang::ASTType::GreaterEqual;
        input.Next();
        Expect(input, ADT::Lang::TokenType::Equal);
        return Equal(input, op);
    }

    Expression(op);
    return op;
}
