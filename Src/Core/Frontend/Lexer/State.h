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
        bool StringLiteral = false;
        bool NumberLiteral = false;
        bool FloatLiteral = false;

    public:
        void Reset()
        {
            StringLiteral = false;
            NumberLiteral = false;
            FloatLiteral = false;
        }

        [[nodiscard]] bool IsStringLiteral() const
        {
            return StringLiteral;
        }

        [[nodiscard]] bool IsNumberLiteral() const
        {
            return NumberLiteral;
        }

        [[nodiscard]] bool IsFloatLiteral() const
        {
            return FloatLiteral;
        }

        void ToggleStringLiteral()
        {
            StringLiteral = !StringLiteral;
        }

        void ToggleNumberLiteral()
        {
            NumberLiteral = !NumberLiteral;
        }

        void ToggleFloatLiteral()
        {
            FloatLiteral = !FloatLiteral;
        }
    };
}