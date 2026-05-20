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
#include <Celery/String/External.h>


#include <climits>

namespace Typed::Support::Strconv
{
    inline int ParseInt(Celery::Str::External &str)
    {
        auto size = str.Size();
        size_t i = 0;

        // Skip leading whitespace
        while (
            i < size &&
            std::isspace(
                static_cast<unsigned char>(str[i])
            )
        )
            ++i;

        // Sign
        int sign = 1;
        if (i < size)
        {
            if (str[i] == '-')
            {
                sign = -1;
                ++i;
            }
            else if (str[i] == '+')
            {
                ++i;
            }
        }

        // Parse digits
        long long result = 0;
        while (i < size)
        {
            char c = str[i];
            if (c < '0' || c > '9')
                break;

            result = result * 10 + (c - '0');

            // Early stop if result already too large
            if (result > static_cast<long long>(INT_MAX) + 1)
                break;

            ++i;
        }

        result *= sign;

        // Clamp to int range
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        return static_cast<int>(result);
    }
}