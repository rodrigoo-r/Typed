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
#include <vector>

#include "ADT/Memory/HeapRef.h"

// Forward declaration
namespace Typed::ADT::Runtime
{
    struct Object;
}

namespace Typed::ADT::List
{
    using Object =
        std::vector<Runtime::Object>;

    using DynamicObject =
        Memory::HeapRef<
            std::vector<Runtime::Object>
        >;
}