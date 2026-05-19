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
#include "ADT/Runtime/ObjectType.h"

namespace Typed::ADT::PreWalker
{
    struct Procedure
    {
        using Tree =
            Lang::AST;

        using TreePtr =
            Tree *;

        using ArgumentMap =
            Map::Dense<
                Celery::Str::External,
                Runtime::ObjectType,
                Celery::Misc::Hash
            >;

        ArgumentMap arguments;
        TreePtr body;
    };
}