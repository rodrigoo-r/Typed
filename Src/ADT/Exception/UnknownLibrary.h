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
#include <string_view>

namespace Typed::ADT::Exception
{
    class UnknownLibrary :
        public Base
    {
        std::string_view &name;

    public:
        UnknownLibrary(
            std::string_view &name
        ) :
            Base("Unknown library"),
            name(name)
        {}

        [[nodiscard]] std::string_view &GetName()
        const {
            return name;
        }
    };
}