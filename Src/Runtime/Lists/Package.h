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
#include "Pop.h"
#include "Set.h"
#include "Size.h"

namespace Typed::Runtime::Lists
{
    inline ADT::Map::Procedure Package = {
        {
            "List_Add",
            {
                {
                    {"l", ADT::Runtime::ObjectType::List},
                    {"_", ADT::Runtime::ObjectType::Any},
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                true,
                Add
            }
        },
        {
            "List_Pop",
            {
                {
                    {"l", ADT::Runtime::ObjectType::List}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                Pop
           }
        },
        {
            "List_Size",
            {
                {
                    {"l", ADT::Runtime::ObjectType::List}
                },
                nullptr,
                ADT::Runtime::ObjectType::Integer,
                false,
                Size
            }
        },
        {
            "List_Access",
            {
                {
                    {"l", ADT::Runtime::ObjectType::List},
                    {"i", ADT::Runtime::ObjectType::Integer}
                },
                nullptr,
                ADT::Runtime::ObjectType::Any,
                false,
                Access
            }
        },
        {
            "List_Set",
            {
                {
                    {"l", ADT::Runtime::ObjectType::List},
                    {"i", ADT::Runtime::ObjectType::Integer},
                    {"o", ADT::Runtime::ObjectType::Any}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                Set
            }
        }
    };
}