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
#include <Celery/Array/Vector.h>
#include <Celery/String/External.h>


#include "ADT/Core/Traceable.h"
#include "ASTType.h"

namespace Typed::ADT::Lang
{
    struct AST :
        Core::Traceable
    {
        ASTType type;
        Celery::Str::External value;
        Celery::Array::Vector<AST *> children;
    };
}