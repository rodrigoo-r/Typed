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
// Created by Rodrigo on 5/27/26.
//

#pragma once
#include "ADT/Exception/MismatchedType.h"
#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Support::Math
{
    inline ADT::Runtime::Object Calculate(
        ADT::List::Object &args,
        ADT::Lang::AST *trace,
        float (*func)(float)
    )
    {
        auto &target = args[0];
        if (target.type == ADT::Runtime::ObjectType::Float)
        {
            auto &val = Runtime::GetFloatObj(target);
            return {
                ADT::Runtime::ObjectType::Float,
                func(val)
            };
        }

        if (target.type == ADT::Runtime::ObjectType::Integer)
        {
            auto &val = Support::Runtime::GetIntObj(target);
            return {
                ADT::Runtime::ObjectType::Float,
                func(static_cast<float>(val))
            };
        }

        throw ADT::Exception::MismatchedType(
            trace->line,
            trace->column
        );
    }
}