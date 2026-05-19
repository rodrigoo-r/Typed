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

Machine::TreePtr Machine::CallMethod(
    TokenStreamView &input,
    ExprQueue &queue
)
{
    auto &name = input.Peek();
    Expect(input, ADT::Lang::TokenType::Identifier);

    // Allocate the CallMethod node
    auto call = AllocateBase(name, ADT::Lang::ASTType::CallMethod);
    call->children.PushBack(AllocateBase(name, ADT::Lang::ASTType::Identifier));

    Expect(input, ADT::Lang::TokenType::From);
    auto &from = input.Peek();
    Expect(input, ADT::Lang::TokenType::Identifier);
    call->children.PushBack(AllocateBase(from, ADT::Lang::ASTType::Identifier));

    // Parse arguments if any
    if (!tokens.HasNext()) return call;
    Expect(input, ADT::Lang::TokenType::With);
    call->children.PushBack(CallArgs(input, queue));

    return call;
}
