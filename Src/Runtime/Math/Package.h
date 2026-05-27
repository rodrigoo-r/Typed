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
                false,
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
                false,
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
                false,
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
                false,
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
                false,
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
                false,
                HyperbolicTangent
            }
        }
    };
}