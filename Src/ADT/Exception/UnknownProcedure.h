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

#include "ADT/Core/Traceable.h"
#include "Traceable.h"

namespace Typed::ADT::Exception
{
    class UnknownProcedure :
        public Traceable
    {
    public:
        UnknownProcedure(
            size_t line,
            size_t column
        ) :
            Traceable(
                "Unknown procedure",
                line,
                column
            )
        {}
    };
}