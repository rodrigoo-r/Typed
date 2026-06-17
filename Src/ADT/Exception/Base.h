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
// Created by Rodrigo on 5/30/26.
//

#pragma once

#include <exception>

namespace Typed::ADT::Exception
{
    class Base :
        public std::exception
    {
        const char *msg = nullptr;

    public:
        Base(const char *msg)
        {
            this->msg = msg;
        }

        [[nodiscard]] const char *what() const noexcept override
        {
            return msg;
        }
    };
}