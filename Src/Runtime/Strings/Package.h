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
#include "Access.h"
#include "Add.h"
#include "Contains.h"
#include "FindIndex.h"
#include "FindIndexes.h"
#include "ReplaceAll.h"
#include "ReplaceMany.h"
#include "ReplaceOne.h"
#include "Size.h"
#include "Trim.h"
#include "TrimLeft.h"
#include "TrimRight.h"

namespace Typed::Runtime::Strings
{
    inline ADT::Map::Procedure Package = {
        {
            "String_Size",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                Size
            }
        },
        {
            "String_Access",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"i", ADT::Runtime::ObjectType::Integer}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                Access
            }
        },
        {
            "String_Add",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"s", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                Add
            }
        },
        {
            "String_Trim_Left",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                TrimLeft
            }
        },
        {
            "String_Trim_Right",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                TrimRight
            }
        },
        {
            "String_Trim",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                Trim
            }
        },
        {
            "String_Contains",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                Contains
            }
        },
        {
            "String_Find_Index",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Integer,
                false,
                FindIndex
            }
        },
        {
            "String_Find_Indexes",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String},
                    {"m", ADT::Runtime::ObjectType::Integer}
                },
                nullptr,
                ADT::Runtime::ObjectType::List,
                false,
                FindIndexes
            }
        },
        {
            "String_Replace_One",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"l", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                ReplaceOne
            }
        },
        {
            "String_Replace_Many",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"l", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String},
                    {"m", ADT::Runtime::ObjectType::Integer}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                ReplaceMany
            }
        },
        {
            "String_Replace_All",
            {
                {
                    {"s", ADT::Runtime::ObjectType::String},
                    {"l", ADT::Runtime::ObjectType::String},
                    {"t", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                ReplaceAll
            }
        }
    };
}