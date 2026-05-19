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

#include "Translator.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Bytecode;

void Translator::Translate()
{
    for (auto &child : core->children)
    {
        switch (child->type)
        {
            case ADT::Lang::ASTType::Use:
            {
                break;
            }

            case ADT::Lang::ASTType::Procedure:
            {
                break;
            }

            default: break;
        }
    }
}
