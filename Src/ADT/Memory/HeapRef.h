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
// Created by Rodrigo on 5/24/26.
//

#pragma once
#include "Support/Allocator/Monotonic.h"

namespace Typed::ADT::Memory
{
    template <
        typename T,
        typename Allocator = Support::Allocator::Monotonic<T>
    >
    class HeapRef
    {
        T *ptr = nullptr;

    public:
        HeapRef(auto &&...args)
        {
            ptr = Allocator::Allocate(std::forward<decltype(args)>(args)...);
        }

        T *operator->()
        {
            return ptr;
        }

        T &operator*()
        {
            return *ptr;
        }
    };
}