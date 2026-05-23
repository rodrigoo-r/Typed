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
#include <deque>


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

        struct ExpressionQueueElement
        {
            TokenStreamView tokens;
            TreePtr parent;
        };

        struct BodyQueueElement
        {
            TreePtr body;
            ADT::Lang::Token &match;
        };

        using ExprQueue =
            Celery::Array::Vector<ExpressionQueueElement>;

        using BodyQueue =
            std::deque<BodyQueueElement>;

        Lexer::Machine::StreamRef tokens;

        TreePtr root = nullptr;

        TreePtr AllocateBase(
            ADT::Lang::Token &token,
            ADT::Lang::ASTType type
        );

        TreePtr Allocate(ADT::Lang::ASTType type);

        void Expect(ADT::Lang::TokenType type);
        void Expect(TokenStreamView &input, ADT::Lang::TokenType type);

        void Use();
        void Procedure();

        void Declare(TreePtr parent);

        void Expression(TreePtr parent);
        void Expression(TreePtr body, TokenStreamView &input);
        void Return(TreePtr parent);
        void If(TreePtr parent, BodyQueue &body_queue);

        void For(TreePtr parent, BodyQueue &body_queue);
        void EndFor(BodyQueue &body_queue);

        void While(TreePtr parent, BodyQueue &body_queue);
        void EndWhile(BodyQueue &body_queue);

        TreePtr ConditionGroup(TreePtr parent, BodyQueue &body_queue);
        void ElseIf(TreePtr parent, BodyQueue &body_queue);
        void Else(TreePtr parent, BodyQueue &body_queue);
        void EndIf(BodyQueue &body_queue);

        TreePtr CallArgs(TokenStreamView &input, ExprQueue &queue);
        TreePtr Call(TokenStreamView &input, ExprQueue &queue);

        TreePtr ArithmeticLHS(TokenStreamView &input);
        TreePtr ArithmeticBase(TokenStreamView &input, ADT::Lang::TokenType delimiter);
        TreePtr Add(TokenStreamView &input);
        TreePtr Sub(TokenStreamView &input);
        TreePtr Mul(TokenStreamView &input);
        TreePtr Div(TokenStreamView &input);
        TokenStreamView ExtractUntilBoolean(
            TokenStreamView &input,
            bool throw_unmatched = true
        );
        TreePtr BooleanOperation(
            TokenStreamView &input,
            TreePtr result,
            ExprQueue &queue
        );
        TreePtr BooleanOperator(
            TokenStreamView &input,
            TreePtr result,
            ExprQueue &queue
        );

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