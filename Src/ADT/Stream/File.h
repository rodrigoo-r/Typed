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
// Created by Rodrigo on 5/16/26.
//

#pragma once

#include <Celery/Array/External.h>
#include <Celery/Array/Stream.h>

namespace Typed::ADT::Stream
{
    using FileView =
        Celery::Array::Pmr::Stream<
            char,
            Celery::Array::External<char>
        >;

    using File =
        Celery::Array::Stream<char>;
}