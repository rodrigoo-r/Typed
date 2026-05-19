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

#include "Support/Stream/Expect.h"


#include "Parser.h"
#include "Support/Equality/TokenType.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Expect(
    TokenStreamView &input,
    ADT::Lang::TokenType type
)
{
    Support::Stream::Expect<
        ADT::Lang::Token,
        TokenStreamView,
        Support::Equality::TokenType
    >(input, type);
}

void Machine::Expect(ADT::Lang::TokenType type)
{
    Support::Stream::Expect<
        ADT::Lang::Token,
        Lexer::Machine::StreamRef,
        Support::Equality::TokenType
    >(tokens, type);
}
