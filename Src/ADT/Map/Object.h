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
// Created by Rodrigo on 5/23/26.
//

#pragma once
#include "Dense.h"
#include "Support/Equality/Object.h"
#include "Support/Hash/Object.h"

// Forward declaration
namespace Typed::ADT::Runtime
{
    struct Object;
}

namespace Typed::ADT::Map
{
    using Object =
        Dense<
            Runtime::Object,
            Runtime::Object,
            Support::Equality::Object,
            Support::Hash::AgnosticObject<Runtime::Object>
        >;
}