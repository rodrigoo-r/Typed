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
#include <memory>

namespace Typed::ADT::Memory
{
    template <typename T>
    class HeapRef :
        public std::shared_ptr<T>
    {
    public:
        static HeapRef Make(auto &&...args)
        {
            return static_cast<HeapRef>(std::make_shared<T>(std::forward<decltype(args)>(args)...));
        }
    };
}