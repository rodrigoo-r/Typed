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

#include "Label.h"

namespace Typed::ADT::Bytecode
{
    struct Procedure
    {
        using LabelList =
            Celery::Array::SmallVector<Label>;

        LabelList labels;
        int entry_point; // The entry label's index
    };
}