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
// Created by Rodrigo on 5/20/26.
//

#pragma once

#include "ADT/Map/Procedure.h"
#include "Add.h"
#include "Support/Printer/ASTPrinter.h"

namespace Typed::Runtime::Dictionaries
{
    inline ADT::Map::Procedure Package = {
        {
            "Dictionary_Add",
            {
                {
                    {"d", ADT::Runtime::ObjectType::Dictionary},
                    {"k", ADT::Runtime::ObjectType::Any},
                    {"v", ADT::Runtime::ObjectType::Any},
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                Add
            }
        }
    };
}