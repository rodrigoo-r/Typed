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
// Created by Rodrigo on 5/29/26.
//

#pragma once
#include <Celery/String/String.h>

#include "ADT/Runtime/Object.h"

namespace Typed::Support::Runtime
{
    inline Celery::Str::String ConvertToString(
        const Celery::Str::External &obj
    )
    {
        return {
            obj.Ptr(),
            obj.Size()
        };
    }
}