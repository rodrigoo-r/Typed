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
// Created by Rodrigo on 6/8/26.
//

#pragma once


#include "Runtime/IO/Package.h"
#include "Runtime/Strings/Unescape.h"

namespace Typed::Support::Runtime
{
    inline ADT::Runtime::Object NormalizeObject(
        ADT::Runtime::Object &obj,
        ADT::Lang::AST *trace
    )
    {
        if (obj.type == ADT::Runtime::ObjectType::String)
        {
            return Typed::Runtime::Strings::Unescape(obj, trace);
        }

        return std::move(obj);
    }
}