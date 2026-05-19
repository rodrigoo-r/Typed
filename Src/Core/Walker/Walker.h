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
#include "ADT/Lang/AST.h"

namespace Typed::Core::Walker
{
    class Machine
    {
    public:
        using Tree =
            ADT::Lang::AST;

        using TreePtr =
            Tree *;

    protected:
        TreePtr root;

        void Procedure(TreePtr ast);

    public:
        Machine(TreePtr root)
            : root(root)
        {}

        void Walk();
    };
}