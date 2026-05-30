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

#include "ADT/Exception/Traceable.h"

namespace Typed::ADT::Exception
{
    class MismatchedArgCount :
        public Traceable
    {
    public:
        MismatchedArgCount(
            Celery::Trait::VeryLarge line,
            Celery::Trait::VeryLarge column
        ) :
            Traceable(
                "Mismatched argument count",
                line,
                column
            )
        {}
    };
}