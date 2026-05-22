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

Machine::TreePtr Machine::Less(
    TokenStreamView &input,
    TreePtr op
)
{
    // Reuse the same logic from Greater
    Greater(input, op);

    if (op->type == ADT::Lang::ASTType::GreaterEqual)
    {
        op->type = ADT::Lang::ASTType::LessEqual;
    } else
    {
        op->type = ADT::Lang::ASTType::Less;
    }

    return op;
}
