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

#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Walker;

void Machine::Walk()
{
    for (auto ast : root->children)
    {
        switch (ast->type)
        {
            case ADT::Lang::ASTType::Procedure:
            {
                Procedure(ast);
                break;
            }

            case ADT::Lang::ASTType::Use:
            {
                break;
            }

            default: break;
        }
    }
}
