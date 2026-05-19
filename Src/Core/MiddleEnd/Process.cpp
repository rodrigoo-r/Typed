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

#include "PreWalker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::MiddleEnd;

PreWalker::RunnableRef PreWalker::Process()
{
    for (auto ast : root->children)
    {
        switch (ast->type)
        {
            case ADT::Lang::ASTType::Use:
            {
                Use(ast);
                break;
            }

            case ADT::Lang::ASTType::Procedure:
            {
                Procedure(ast);
                break;
            }

            default: break;
        }
    }

    return result;
}
