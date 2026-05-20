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
// Created by Rodrigo on 5/18/26.
//

#pragma once

#include <Celery/Misc/Hash.h>
#include <Celery/String/External.h>


#include "ADT/PreWalker/Procedure.h"
#include "Dense.h"

namespace Typed::ADT::Map
{
    using Procedure =
        Dense<
            Celery::Str::External,
            PreWalker::Procedure,
            Celery::Misc::Hash
        >;
}