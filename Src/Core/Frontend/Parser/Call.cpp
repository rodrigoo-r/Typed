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
#include "Support/Stream/SafePeek.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

Machine::TreePtr Machine::Call(
    TokenStreamView &input,
    ExprQueue &queue
)
{
    auto &name = Support::Stream::SafePeek(input);
    Expect(input, ADT::Lang::TokenType::Identifier);

    // Allocate the call node
    auto call = AllocateBase(name, ADT::Lang::ASTType::Call);
    call->children.push_back(AllocateBase(name, ADT::Lang::ASTType::Identifier));

    // Stop parsing arguments if needed
    auto &peek = Support::Stream::SafePeek(input);
    if (peek.type == ADT::Lang::TokenType::EndCall)
    {
        input.Next();
        return call;
    }

    // Parse arguments if needed
    Expect(input, ADT::Lang::TokenType::With);
    call->children.push_back(CallArgs(input, queue));

    return call;
}
