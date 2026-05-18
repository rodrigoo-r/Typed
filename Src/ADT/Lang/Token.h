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
// Created by Rodrigo on 5/16/26.
//

#pragma once
#include <Celery/String/External.h>

#include "ADT/Core/Traceable.h"
#include "TokenType.h"

namespace Typed::ADT::Lang
{
    struct Token :
        Core::Traceable
    {
        Celery::Str::External value;
        TokenType type;
    };
}