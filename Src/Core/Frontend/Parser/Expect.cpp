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

#include "ADT/Exception/UnknownToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Expect(ADT::Lang::TokenType type)
{
    // Edge case: No tokens
    if (tokens.Empty())
    {
        // Exception at line 1 column 1
        throw ADT::Exception::UnknwonToken(1, 1);
    }

    if (!tokens.HasNext())
    {
        auto &curr = tokens.Curr();

        throw ADT::Exception::UnknwonToken(
            curr.line,
            curr.column
        );
    }

    auto &token = tokens.Peek();
    if (token.type != type)
    {
        throw ADT::Exception::UnknwonToken(
            token.line,
            token.column
        );
    }
}
