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

Machine::TreePtr Machine::Call(
    TokenStreamView &input,
    ExprQueue &queue
)
{
    auto &name = input.Peek();
    Expect(input, ADT::Lang::TokenType::Identifier);

    // Allocate the call node
    auto call = AllocateBase(name, ADT::Lang::ASTType::Call);
    call->children.PushBack(AllocateBase(name, ADT::Lang::ASTType::Identifier));

    // Parse arguments if needed
    if (!input.HasNext()) return call;
    Expect(input, ADT::Lang::TokenType::With);
    call->children.PushBack(CallArgs(input, queue));

    return call;
}
