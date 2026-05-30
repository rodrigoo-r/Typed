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
#include "CosineDegrees.h"
#include "CosineRadians.h"
#include "HyperbolicCosineDegrees.h"
#include "HyperbolicCosineRadians.h"
#include "HyperbolicSineDegrees.h"
#include "HyperbolicSineRadians.h"
#include "HyperbolicTangentDegrees.h"
#include "HyperbolicTangentRadians.h"
#include "RadiansToDegrees.h"
#include "SineDegrees.h"
#include "SineRadians.h"
#include "TangentDegrees.h"
#include "TangentRadians.h"

namespace Typed::Runtime::Math
{
    inline ADT::Map::Procedure Package = {
        {
            "Sine_Radians",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                SineRadians
            }
        },
        {
            "Cosine_Radians",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                CosineRadians
            }
        },
        {
            "Tangent_Radians",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                TangentRadians
            }
        },
        {
            "Hyperbolic_Sine_Radians",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                HyperbolicSineRadians
            }
        },
        {
            "Hyperbolic_Cosine_Radians",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                HyperbolicCosineRadians
            }
        },
        {
            "Hyperbolic_Tangent_Radians",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                HyperbolicTangentRadians
            }
        },
        {
            "Sine_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                SineDegrees
            }
        },
        {
            "Cosine_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                CosineDegrees
            }
        },
        {
            "Tangent_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                TangentDegrees
            }
        },
        {
            "Hyperbolic_Sine_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                HyperbolicSineDegrees
            }
        },
        {
            "Hyperbolic_Cosine_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                HyperbolicCosineDegrees
            }
        },
        {
            "Hyperbolic_Tangent_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                HyperbolicTangentDegrees
            }
        },
        {
            "Radians_To_Degrees",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                false,
                RadiansToDegrees
            }
        }
    };
}