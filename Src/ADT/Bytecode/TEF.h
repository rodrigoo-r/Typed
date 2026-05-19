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
#include <Celery/Array/SmallVector.h>

#include "Procedure.h"

namespace Typed::ADT::Bytecode
{
    // TEF = Typed Executable Format
    // A small executable format that
    // the Typed VM runs
    struct TEF
    {
        using ProcedureList =
            Celery::Array::SmallVector<Procedure>;

        // List of procedures
        ProcedureList procedures;

        // Entry point's idx
        Celery::Trait::VeryLarge entry_point = 0;
    };
}