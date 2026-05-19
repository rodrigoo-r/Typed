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
#include "ADT/PreWalker/File.h"

namespace Typed::Core::MiddleEnd
{
    class PreWalker
    {
        using Tree =
            ADT::Lang::AST;

        using TreePtr =
            Tree *;

    public:
        using Runnable =
            ADT::PreWalker::File;

        using RunnableRef =
            Runnable &;

    protected:
        TreePtr root;
        Runnable result;

        void Use();
        void Procedure();

    public:
        PreWalker(TreePtr root)
            : root(root)
        {}

        RunnableRef Process();
    };
}