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
#include "ADT/Stream/External.h"
#include "ADT/Stream/Token.h"
#include "Core/Frontend/Lexer/Lexer.h"
#include "Support/Allocator/Monotonic.h"

namespace Typed::Core::Frontend::Parser
{
    class Machine
    {
    public:
        using TokenStreamView =
            ADT::Stream::External<ADT::Lang::Token>;

        using Tree =
            ADT::Lang::AST;

        using TreePtr =
            Tree *;

    protected:
        using Allocator =
            Support::Allocator::Monotonic<
                ADT::Lang::AST
            >;

        Lexer::Machine::StreamRef tokens;

        TreePtr root = nullptr;

        TreePtr AllocateBase(
            ADT::Lang::Token &token,
            ADT::Lang::ASTType type
        );

        TreePtr Allocate(ADT::Lang::ASTType type);

        void Expect(ADT::Lang::TokenType type);

        void Use();
        void Procedure();

        void Declare(TreePtr parent);

        void Expression(TreePtr parent);
        void Expression(TreePtr body, TokenStreamView &input);

        TreePtr CallArgs(TokenStreamView &input);
        TreePtr Call(TokenStreamView &input);
        TreePtr CallMethod(TokenStreamView &input);
        TreePtr Add(TokenStreamView &input);
        TreePtr Sub(TokenStreamView &input);
        TreePtr Mul(TokenStreamView &input);
        TreePtr Div(TokenStreamView &input);

        TreePtr Type();

    public:
        Machine(Lexer::Machine::StreamRef tokens) :
            tokens(tokens)
        {
            root = AllocateBase(tokens.Peek(), ADT::Lang::ASTType::Root);
        }

        TreePtr Parse();
    };
}