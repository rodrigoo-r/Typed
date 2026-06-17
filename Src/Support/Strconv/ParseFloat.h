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

#include <limits>
#include <string_view>

namespace Typed::Support::Strconv
{
    inline float ParseFloat(std::string_view str)
    {
        auto size = str.size();
        size_t i = 0;

        // Skip leading whitespace
        while (
            i < size &&
            std::isspace(static_cast<unsigned char>(str[i]))
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

        // Parse integer part
        double intPart = 0.0;
        bool hasDigits = false;
        while (i < size)
        {
            char c = str[i];
            if (c < '0' || c > '9')
                break;

            hasDigits = true;
            intPart = intPart * 10.0 + (c - '0');
            ++i;
        }

        // Fractional part
        double frac = 0.0;
        double fracDiv = 1.0;
        if (i < size && str[i] == '.')
        {
            ++i;
            while (i < size)
            {
                char c = str[i];
                if (c < '0' || c > '9')
                    break;

                hasDigits = true;
                frac = frac * 10.0 + (c - '0');
                fracDiv *= 10.0;
                ++i;
            }
        }

        double value = intPart;
        if (fracDiv > 1.0)
            value += frac / fracDiv;

        // Exponent part
        if (i < size && (str[i] == 'e' || str[i] == 'E'))
        {
            ++i;
            int expSign = 1;
            if (i < size)
            {
                if (str[i] == '-')
                {
                    expSign = -1;
                    ++i;
                }
                else if (str[i] == '+')
                {
                    ++i;
                }
            }

            int exp = 0;
            bool expDigits = false;
            while (i < size)
            {
                char c = str[i];
                if (c < '0' || c > '9')
                    break;

                expDigits = true;
                exp = exp * 10 + (c - '0');
                ++i;
            }

            if (expDigits)
            {
                // use pow with double intermediate for more accuracy
                value *= std::pow(10.0, expSign * exp);
            }
        }

        value *= sign;

        if (!hasDigits)
            return 0.0f;

        // Clamp to float range
        double maxf = std::numeric_limits<float>::max();
        if (value > maxf) return std::numeric_limits<float>::max();
        if (value < -maxf) return -std::numeric_limits<float>::max();

        return static_cast<float>(value);
    }
}