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
#include <Celery/Array/SmallVector.h>

#include "ADT/PreWalker/Procedure.h"

namespace Typed::ADT::List
{
    using Procedure =
        Celery::Array::SmallVector<
            PreWalker::Procedure
        >;
}