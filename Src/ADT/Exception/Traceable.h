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
#include "ADT/Core/Traceable.h"

namespace Typed::ADT::Exception
{
    class Traceable :
        public std::exception,
        public Core::Traceable
    {
        const char *msg = nullptr;

    public:
        Traceable(
            const char *msg,
            size_t line,
            size_t column
        ) :
            Core::Traceable{line, column}
        {
            this->msg = msg;
        }

        [[nodiscard]] const char *what() const noexcept
        {
            return msg;
        }
    };
}