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
// Created by Rodrigo on 5/23/26.
//

#include "ADT/Exception/UnexpectedToken.h"
#include "Parser.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::End(
    ADT::Lang::TokenType received,
    BodyQueue &body_queue
)
{
    auto &last_el = body_queue.front();
    auto &trace = tokens.Next();

    // Make sure the last element matches the block declaration
    if (
        (
            received == ADT::Lang::TokenType::EndFor &&
            last_el.match.type != ADT::Lang::TokenType::For
        ) || (
            received == ADT::Lang::TokenType::EndIf &&
            last_el.match.type != ADT::Lang::TokenType::If &&
            last_el.match.type != ADT::Lang::TokenType::ElseIf &&
            last_el.match.type != ADT::Lang::TokenType::Else
        ) || (
            received == ADT::Lang::TokenType::EndWhile &&
            last_el.match.type != ADT::Lang::TokenType::While
        )
    )
    {
        throw ADT::Exception::UnexpectedToken(
            trace.line,
            trace.column
        );
    }

    // Pop the front element
    body_queue.pop_front();
}
