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
#include "ADT/Map/Dense.h"
#include "Procedure.h"

namespace Typed::ADT::PreWalker
{
    struct File
    {
        using ProcedureMap =
            Map::Dense<
                std::string_view,
                Procedure
            >;

        using ImportList =
            std::vector<
                std::string_view
            >;

        ProcedureMap procedures;
        ImportList imports;
    };
}