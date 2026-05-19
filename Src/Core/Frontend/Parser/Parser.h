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
#include "ADT/Lang/AST.h"
#include "ADT/Stream/Token.h"
#include "Core/Frontend/Lexer/Lexer.h"
#include "Support/Allocator/Monotonic.h"

namespace Typed::Core::Frontend::Parser
{
    class Machine
    {
    protected:
        using Allocator =
            Support::Allocator::Monotonic<
                ADT::Lang::AST
            >;

        using Tree =
            ADT::Lang::AST;

        using TreePtr =
            Tree *;

        TreePtr AllocateBase(
            ADT::Lang::Token &token,
            ADT::Lang::ASTType type
        );

        TreePtr Allocate(ADT::Lang::ASTType type);

        Lexer::Machine::StreamRef tokens;

        void Use();

    public:
        Machine(Lexer::Machine::StreamRef tokens) :
            tokens(tokens)
        {}

        TreePtr Parse();
    };
}