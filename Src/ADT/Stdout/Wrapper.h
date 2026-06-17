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
#include <iostream>

namespace Typed::ADT::Stdout
{
    class Wrapper
    {
    public:
        void append(auto &&arg)
        {
            std::cout
                << std::forward<decltype(arg)>(arg);
        }

        void append(const char *arg, size_t size)
        {
            std::cout <<
                std::string_view{arg, size};
        }

        void append(size_t _, const char arg)
        {
            std::cout << arg;
        }
    };
}