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
#include "ADT/List/Object.h"
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

        ArgumentList arguments;
        TreePtr body;
        Runtime::ObjectType return_type = Runtime::ObjectType::Void;
        bool variadic = false;

        // Used for runtime-provided functions
        void (*native)(List::Object &, TreePtr) = nullptr;
    };
}