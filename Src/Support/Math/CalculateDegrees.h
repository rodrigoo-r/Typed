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
#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"
#include "Calculate.h"

namespace Typed::Support::Math
{
    inline float RadiansToDegrees(const float radians)
    {
        return static_cast<float>(radians * (180 / M_PI));
    }

    inline float RadiansToDegrees(const int radians)
    {
        return RadiansToDegrees(static_cast<float>(radians));
    }

    inline ADT::Runtime::Object CalculateDegrees(
        ADT::List::Object &args,
        ADT::Lang::AST *trace,
        float (*func)(float)
    )
    {
        auto &target = args[0];
        if (target.type == ADT::Runtime::ObjectType::Float)
        {
            auto &val = Runtime::GetFloatObj(target);

            // Convert to degrees
            val = RadiansToDegrees(val);
        }

        if (target.type == ADT::Runtime::ObjectType::Integer)
        {
            auto &val = Runtime::GetIntObj(target);

            // Convert to degrees
            args[0].type = ADT::Runtime::ObjectType::Float;
            args[0].value = RadiansToDegrees(val);
        }

        return Calculate(args, trace, func);
    }
}