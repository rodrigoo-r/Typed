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
#include "Traceable.h"

namespace Typed::ADT::Exception
{
    class MismatchedType :
        public Traceable
    {
    public:
        MismatchedType(
            Celery::Trait::VeryLarge line,
            Celery::Trait::VeryLarge column
        ) :
            Traceable(
                "Mismatched types",
                line,
                column
            )
        {}
    };
}