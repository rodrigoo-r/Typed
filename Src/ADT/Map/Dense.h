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
#include <ankerl/unordered_dense.h>

namespace Typed::ADT::Map
{
    template <
        typename Key,
        typename Value,
        typename Hash = ankerl::unordered_dense::hash<Key>,
        typename Equal = std::equal_to<Key>
    >
    using Dense =
        ankerl::unordered_dense::map<
            Key,
            Value,
            Hash,
            Equal
        >;
}