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
#include <Celery/String/String.h>

#include "ADT/List/Object.h"

namespace Typed::Support::Format
{
    template <typename Adapter>
    void Format(
        Celery::Str::External &fmt,
        ADT::List::Object &args,
        Adapter &adapter,
        Celery::Trait::VeryLarge line,
        Celery::Trait::VeryLarge col
    );
}