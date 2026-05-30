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
    class ExpectedInitialValue :
        public Traceable
    {
    public:
        ExpectedInitialValue(
            Celery::Trait::VeryLarge line,
            Celery::Trait::VeryLarge column
        ) :
            Traceable(
                "Expected an initial value",
                line,
                column
            )
        {}
    };
}