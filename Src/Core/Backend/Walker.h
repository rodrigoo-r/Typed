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

namespace Typed::Core::Backend
{
    class Walker
    {
    public:
        using Runnable =
            ADT::PreWalker::File;

        using RunnableRef =
            Runnable &;

        using ProcedureRef =
            ADT::PreWalker::Procedure &;

        using VariableList =
            Celery::Array::Vector<ADT::Runtime::Object>;

    protected:
        RunnableRef runnable;

        void Procedure(ProcedureRef procedure, VariableList args);

    public:
        Walker(RunnableRef runnable)
            : runnable(runnable)
        {}

        void Walk();
    };
}