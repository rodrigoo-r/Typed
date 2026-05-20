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
#include "Print.h"
#include "PrintLine.h"
#include "ReadLine.h"
#include "Support/Printer/ASTPrinter.h"

namespace Typed::Runtime::IO
{
    inline ADT::Map::Procedure Package = {
        {
            "Print_Line",
            {
                {
                    {"f", ADT::Runtime::ObjectType::String},
                    {"_", ADT::Runtime::ObjectType::Any},
                },
                nullptr,
                true,
                PrintLine
            }
        },
        {
            "Print",
            {
                {
                    {"f", ADT::Runtime::ObjectType::String},
                    {"_", ADT::Runtime::ObjectType::Any},
                },
                nullptr,
                true,
                Print
            },
        },
        {
            "Read_Line",
            {
                {},
                nullptr,
                true,
                ReadLine
            },
        }
    };
}