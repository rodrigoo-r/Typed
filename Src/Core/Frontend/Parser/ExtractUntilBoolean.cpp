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

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TokenStreamView Machine::ExtractUntilBoolean(
    TokenStreamView &input
)
{
    // Collect tokens until we find a delimiter
    Celery::Trait::VeryLarge start = input.Pos();
    Celery::Trait::VeryLarge size = 0;
    auto found_delim = false;

    while (input.HasNext())
    {
        auto &next = input.Next();
        if (
            next.type == ADT::Lang::TokenType::And ||
            next.type == ADT::Lang::TokenType::Or
        )
        {
            found_delim = true;
            break;
        }

        size++;
    }

    // Make sure we found the delimiter
    if (!found_delim)
    {
        throw ADT::Exception::UnexpectedToken(
            input.Curr().line,
            input.Curr().column
        );
    }

    // Construct the view
    return {
        input.Ptr() + start,
        size
    };
}
