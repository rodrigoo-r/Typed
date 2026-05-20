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

#pragma once
#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"
#include "Argument.h"

namespace Typed::ADT::PreWalker
{
    struct Procedure
    {
        using Tree =
            Lang::AST;

        using TreePtr =
            Tree *;

        using ArgumentList =
            Celery::Array::Vector<Argument>;

        using ObjectList =
            Celery::Array::Vector<Runtime::Object>;

        ArgumentList arguments;
        TreePtr body;

        // Used for runtime-provided functions
        void (*native)(ObjectList);
    };
}