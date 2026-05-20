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

namespace Typed::ADT::Exception
{
    class UnknownLibrary :
        public Celery::Except::Exception,
        public Core::Traceable
    {
    public:
        UnknownLibrary(
            Celery::Trait::VeryLarge line,
            Celery::Trait::VeryLarge column
        ) :
            Exception("Unknown library"),
            Traceable{line, column}
        {}
    };
}