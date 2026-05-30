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
#include <Celery/Except/Base.h>

#include "ADT/Core/Traceable.h"
#include "Traceable.h"

namespace Typed::ADT::Exception
{
    class UnknownSymbol :
        public Traceable
    {
    public:
        UnknownSymbol(
            Celery::Trait::VeryLarge line,
            Celery::Trait::VeryLarge column
        ) :
            Traceable(
                "Unknown symbol",
                line,
                column
            )
        {}
    };
}