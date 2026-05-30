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
#include <Celery/Except/Base.h>
#include <Celery/String/External.h>

namespace Typed::ADT::Exception
{
    class UnknownLibrary :
        public Celery::Except::Exception
    {
        Celery::Str::External &name;

    public:
        UnknownLibrary(
            Celery::Str::External &name
        ) :
            Exception("Unknown library"),
            name(name)
        {}

        [[nodiscard]] Celery::Str::External &GetName()
        const {
            return name;
        }
    };
}