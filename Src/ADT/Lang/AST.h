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
// Created by Rodrigo on 5/18/26.
//

#pragma once

#include <vector>


#include "ADT/Core/Traceable.h"
#include "ASTType.h"

namespace Typed::ADT::Lang
{
    struct AST :
        Core::Traceable
    {
        ASTType type;
        std::string_view value;
        std::vector<AST *> children;
    };
}