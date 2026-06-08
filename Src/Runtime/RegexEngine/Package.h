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

#include "ADT/Map/Procedure.h"
#include "ExtractMatches.h"
#include "MatchesFully.h"
#include "MatchesPartly.h"
#include "ReplaceAll.h"
#include "ReplaceOne.h"

namespace Typed::Runtime::RegexEngine
{
    inline ADT::Map::Procedure Package = {
        {
            "Regex_Extract_Matches",
            {
                {
                    {"r", ADT::Runtime::ObjectType::Regex},
                    {"s", ADT::Runtime::ObjectType::String},
                },
                nullptr,
                ADT::Runtime::ObjectType::List,
                false,
                ExtractMatches
            }
        },
        {
            "Regex_Matches_Fully",
            {
                {
                    {"r", ADT::Runtime::ObjectType::Regex},
                    {"s", ADT::Runtime::ObjectType::String},
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                MatchesFully
            }
        },
        {
            "Regex_Matches_Partly",
            {
                {
                    {"r", ADT::Runtime::ObjectType::Regex},
                    {"s", ADT::Runtime::ObjectType::String},
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                MatchesPartly
            }
        },
        {
            "Regex_Replace_All",
            {
                {
                    {"r", ADT::Runtime::ObjectType::Regex},
                    {"s", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                ReplaceAll
            }
        },
        {
            "Regex_Replace_One",
            {
                {
                    {"r", ADT::Runtime::ObjectType::Regex},
                    {"s", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                ReplaceOne
            }
        }
    };
}