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
#include <Celery/String/External.h>
#include <Celery/String/String.h>


#include "ObjectType.h"

namespace Typed::ADT::Runtime
{
    struct Object
    {
        // A value can hold either of the 4
        // primitives allowed
        using Value =
            std::variant<
                int,
                float,
                bool,
                Celery::Str::External,

                // Only runtime-provided functions can
                // return owned memory
                Celery::Str::String
            >;

        ObjectType type;
        Value value;
    };
}