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
#include <Celery/Misc/Hash.h>


#include "ADT/Lang/AST.h"
#include "ADT/Map/Dense.h"
#include "Procedure.h"

namespace Typed::ADT::PreWalker
{
    struct File
    {
        using ProcedureMap =
            Map::Dense<
                Celery::Str::External,
                Procedure,
                Celery::Misc::Hash
            >;

        using ImportList =
            Celery::Array::Vector<
                Celery::Str::External
            >;

        ProcedureMap procedures;
        ImportList imports;
    };
}