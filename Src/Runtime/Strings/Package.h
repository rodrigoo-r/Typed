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
// Created by Rodrigo on 5/24/26.
//

#pragma once

#include "ADT/Map/Procedure.h"
#include "Size.h"

namespace Typed::Runtime::Strings
{
    inline ADT::Map::Procedure Package = {
        {
            "String_Size",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                Size
            }
        }
    };
}