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
// Created by Rodrigo on 5/16/26.
//

#pragma once

namespace Typed::Core::Frontend::Lexer
{
    class State
    {
        bool string_literal = false;
        bool number_literal = false;
        bool float_literal = false;

    public:
        void Reset()
        {
            string_literal = false;
            number_literal = false;
            float_literal = false;
        }

        [[nodiscard]] bool IsStringLiteral() const
        {
            return string_literal;
        }

        [[nodiscard]] bool IsNumberLiteral() const
        {
            return number_literal;
        }

        [[nodiscard]] bool IsFloatLiteral() const
        {
            return float_literal;
        }

        void ToggleStringLiteral()
        {
            string_literal = !string_literal;
        }

        void ToggleNumberLiteral()
        {
            number_literal = !number_literal;
        }

        void ToggleFloatLiteral()
        {
            float_literal = !float_literal;
        }
    };
}