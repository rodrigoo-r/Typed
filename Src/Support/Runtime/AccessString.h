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

#include "ADT/Runtime/Object.h"

namespace Typed::Support::Runtime
{
    inline std::string_view AccessString(ADT::Runtime::Object &obj)
    {
        if (std::holds_alternative<std::string_view>(obj.value))
            return GetStrObj(obj);

        auto &str = GetOwnedStrObj(obj);
        return {str.data(), str.size()};
    }
}