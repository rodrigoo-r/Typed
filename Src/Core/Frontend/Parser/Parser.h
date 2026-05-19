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
    public:
        using Allocator =
            Support::Allocator::Monotonic<
                ADT::Lang::AST
            >;

        using Tree =
            ADT::Lang::AST;

        using TreePtr =
            Tree *;

        using TokenStreamView =
            Celery::Array::External<ADT::Lang::Token>;

    protected:
        TokenStreamView tokens;

        TreePtr root = nullptr;
        TreePtr AllocateBase(
            ADT::Lang::Token &token,
            ADT::Lang::ASTType type
        );

        TreePtr Allocate(ADT::Lang::ASTType type);

        void Expect(ADT::Lang::TokenType type);

        void Use();
        void Procedure();

        void Declare(TreePtr body);
        void Expression(TreePtr body);

        TreePtr Type();

    public:
        Machine(Lexer::Machine::StreamRef tokens) :
            tokens(tokens.Ptr(), tokens.Size())
        {
            root = AllocateBase(tokens.Peek(), ADT::Lang::ASTType::Root);
        }

        TreePtr Parse();
    };
}