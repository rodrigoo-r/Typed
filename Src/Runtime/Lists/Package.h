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
#include "Add.h"
#include "Pop.h"
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
                    ADT::Runtime::ObjectType::Void,
                    false,
                    Size
               }
        }
    };
}