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

#include <list>
#include <memory_resource>

namespace Typed::Support::Allocator
{
    template <typename Value>
    class Monotonic
    {
        inline static std::pmr::monotonic_buffer_resource resource;
        inline static std::pmr::list<Value *> freed{&resource};

    public:
        template <typename... Args>
        static Value *Allocate(Args &&... args)
        {
            // Check the free list
            Value *ptr = nullptr;

            if (!freed.empty())
            {
                ptr = freed.back();
                ptr->~Value();
                freed.pop_back();
            } else
            {
                ptr = (Value *)resource.allocate(
                    sizeof(Value),
                    alignof(Value)
                );
            }

            return new (ptr) Value(std::forward<Args>(args)...);
        }

        static inline void Deallocate(Value *ptr)
        {
            freed.push_back(ptr);
        }

        ~Monotonic()
        {
            freed.clear();
            resource.release();
        }
    };
}