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
// Created by Rodrigo on 5/20/26.
//

#pragma once
#include <Celery/Array/SmallVector.h>

// Forward declaration
namespace Typed::ADT::Runtime
{
    struct Object;
}

namespace Typed::ADT::List
{
    using Object =
        Celery::Array::SmallVector<
            Runtime::Object
        >;

    using DynamicObject =
        Celery::Array::Vector<
            Runtime::Object
        >;
}