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
#include "Cosine.h"
#include "HyperbolicCosine.h"
#include "HyperbolicSine.h"
#include "HyperbolicTangent.h"
#include "Sine.h"
#include "Tangent.h"

namespace Typed::Runtime::Math
{
    inline ADT::Map::Procedure Package = {
        {
            "Sine",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                true,
                Sine
            }
        },
        {
            "Cosine",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                true,
                Cosine
            }
        },
        {
            "Tangent",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                true,
                Tangent
            }
        },
        {
            "Hyperbolic_Sine",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                true,
                HyperbolicSine
            }
        },
        {
            "Hyperbolic_Cosine",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                true,
                HyperbolicCosine
            }
        },
        {
            "Hyperbolic_Tangent",
            {
                {
                    {"l", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Float,
                true,
                HyperbolicTangent
            }
        }
    };
}