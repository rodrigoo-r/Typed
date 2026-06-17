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
// Created by Rodrigo on 5/21/26.
//

#include "Parser.h"
#include "Support/Stream/SafePeek.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Return(TreePtr parent)
{
    // Allocate the return node
    auto node = Allocate(
        ADT::Lang::ASTType::Return
    );

    parent->children.push_back(node);

    // Parse the expression
    Expression(node);
}
