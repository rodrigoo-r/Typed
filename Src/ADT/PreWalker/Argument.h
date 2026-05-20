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

#pragma once
#include <Celery/String/External.h>

#include "ADT/Runtime/ObjectType.h"

namespace Typed::ADT::PreWalker
{
    struct Argument
    {
        Celery::Str::External name;
        Runtime::ObjectType type;
    };
}