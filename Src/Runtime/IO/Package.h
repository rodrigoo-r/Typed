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

#include "ADT/List/Procedure.h"
#include "Println.h"
#include "Support/Printer/ASTPrinter.h"

namespace Typed::Runtime::IO
{
    inline ADT::List::Procedure Package = {
        {
            {
                {"f", ADT::Runtime::ObjectType::String},
                {"_", ADT::Runtime::ObjectType::Any},
            },
            nullptr,
            true,
            Println
        }
    };
}