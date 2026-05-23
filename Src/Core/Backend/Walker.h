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
#include "ADT/PreWalker/File.h"
#include "ADT/Runtime/Object.h"
#include "ADT/Scope/Stack.h"

namespace Typed::Core::Backend
{
    class Walker
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

        using ProcedureRef =
            ADT::PreWalker::Procedure &;

        using VariableStack =
            ADT::Scope::Stack<
                Celery::Str::External,
                ADT::Runtime::Object,
                Celery::Misc::Hash
            >;

    protected:
        RunnableRef runnable;

        ADT::Runtime::Object Procedure(
            ProcedureRef procedure,
            ADT::List::Object &args,
            TreePtr trace
        );

        ADT::Runtime::Object Body(
            ProcedureRef procedure,
            TreePtr body,
            VariableStack &stack
        );

        void Declare(
            VariableStack &stack,
            TreePtr body
        );

        ADT::Runtime::Object Expression(
            VariableStack &stack,
            TreePtr body
        );

        ADT::Runtime::Object Call(
            VariableStack &stack,
            TreePtr body
        );

        ADT::Runtime::Object Return(
            ProcedureRef procedure,
            VariableStack &stack,
            TreePtr body
        );

        ADT::Runtime::Object Variable(
            VariableStack &stack,
            TreePtr body
        );

        void ArithmeticBase(
            VariableStack &stack,
            TreePtr body
        );

        void Add(
            VariableStack &stack,
            TreePtr body
        );

        void Sub(
            VariableStack &stack,
            TreePtr body
        );

        void Mul(
            VariableStack &stack,
            TreePtr body
        );

        void Div(
            VariableStack &stack,
            TreePtr body
        );

    public:
        Walker(RunnableRef runnable)
            : runnable(runnable)
        {}

        void Walk();
    };
}