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
#include "Support/Stream/SafeNext.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::ArithmeticLHS(TokenStreamView &input)
{
    auto &num = Support::Stream::SafeNext(input);

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

    return AllocateBase(
        num,
        num.type == ADT::Lang::TokenType::NumberLiteral ?
            ADT::Lang::ASTType::NumberLiteral
        : num.type == ADT::Lang::TokenType::FloatLiteral ?
            ADT::Lang::ASTType::FloatLiteral
        : ADT::Lang::ASTType::Identifier
    );
}
