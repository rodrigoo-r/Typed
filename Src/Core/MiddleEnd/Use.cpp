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

void PreWalker::Use(TreePtr ast)
{
    // Push the imported lib to the import list directly
    result.imports.push_back(ast->value);
}
