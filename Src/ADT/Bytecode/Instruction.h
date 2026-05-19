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
// Created by Rodrigo on 5/19/26.
//

#pragma once
#include "Context.h"
#include "InstructionType.h"

namespace Typed::ADT::Bytecode
{
    struct Instruction
    {
        using ArgumentList =
            Celery::Array::SmallVector<Context>;

        InstructionType type;
        ArgumentList arguments;
    };
}