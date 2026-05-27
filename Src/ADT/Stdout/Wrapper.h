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
// Created by Rodrigo on 5/27/26.
//

#pragma once

#include "Support/Printer/ASTPrinter.h"

namespace Typed::ADT::Stdout
{
    class Wrapper
    {
    public:
        void Write(auto &&arg)
        {
            Celery::Io::Print(std::forward<decltype(arg)>(arg));
        }

        void Write(const char *arg, Celery::Trait::VeryLarge size)
        {
            Celery::Io::IStdout.Batch(arg, size);
        }
    };
}