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

    public:
        Machine(TreePtr root)
            : root(root)
        {}

        void Walk();
    };
}