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
#include "ADT/Bytecode/TEF.h"
#include "ADT/Lang/AST.h"

namespace Typed::Core::Bytecode
{
    class Translator
    {
    public:
        using Executable =
            ADT::Bytecode::TEF;

        using ExecutableRef =
            Executable &;

    protected:
        using Tree =
            ADT::Lang::AST;

        using TreePtr =
            Tree *;

        Executable result;
        TreePtr core;

        void Procedure(TreePtr input);
    public:
        Translator(TreePtr core)
            : core(core)
        {}

        ExecutableRef Translate();
    };
}