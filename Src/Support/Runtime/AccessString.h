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
// Created by Rodrigo on 5/25/26.
//

#pragma once
#include <Celery/String/External.h>

#include "ADT/Runtime/Object.h"

namespace Typed::Support::Runtime
{
    Celery::Str::External AccessString(ADT::Runtime::Object &obj)
    {
        if (obj.type == ADT::Runtime::ObjectType::String)
            return GetStrObj(obj);

        auto &str = GetOwnedStrObj(obj);
        return {str.Ptr(), str.Size()};
    }
}