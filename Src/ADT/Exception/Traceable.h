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
// Created by Rodrigo on 5/30/26.
//

#pragma once
#include <Celery/Except/Base.h>

#include "ADT/Core/Traceable.h"
#include "Support/Strconv/ParseFloat.h"

namespace Typed::ADT::Exception
{
    class Traceable :
        public Celery::Except::Exception,
        public Core::Traceable
    {
    public:
        Traceable(
            const char *msg,
            Celery::Trait::VeryLarge line,
            Celery::Trait::VeryLarge column
        ) :
            Exception(msg),
            Core::Traceable{line, column}
        {}
    };
}