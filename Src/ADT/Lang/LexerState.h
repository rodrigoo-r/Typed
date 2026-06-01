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

#include <Celery/Trait/Default.h>

#include "EscapeType.h"

namespace Typed::ADT::Lang
{
    class LexerState
    {
        bool string_literal = false;
        bool number_literal = false;
        bool float_literal = false;
        bool identifier = false;
        bool escape = false;
        Celery::Trait::VeryLarge escape_size = 0;
        Celery::Trait::VeryLarge start = 0;
        Celery::Trait::VeryLarge line = 1;
        Celery::Trait::VeryLarge column = 1;
        Celery::Trait::VeryLarge size = 0;
        Celery::Trait::VeryLarge token_line = 1;
        Celery::Trait::VeryLarge token_column = 1;
        EscapeType escape_type = EscapeType::NoEscape;

    public:
        void Reset()
        {
            string_literal = false;
            number_literal = false;
            float_literal = false;
            identifier = false;
            escape_type = EscapeType::NoEscape;
            escape_size = 0;
            size = 0;
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

        [[nodiscard]] bool IsIdentifier() const
        {
            return identifier;
        }

        [[nodiscard]] bool IsEscape() const
        {
            return escape;
        }

        void ToggleIdentifier()
        {
            identifier = !identifier;
        }

        void ToggleEscape()
        {
            escape = !escape;
            escape_size = 0;
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

        void SetStart(const Celery::Trait::VeryLarge &start)
        {
            this->start = start;
        }

        void SetEscapeType(const EscapeType &type)
        {
            escape_type = type;
        }

        [[nodiscard]] EscapeType GetEscapeType() const
        {
            return escape_type;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetStart() const
        {
            return start;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetLine() const
        {
            return line;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetColumn() const
        {
            return column;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetSize() const
        {
            return size;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetEscapeSize() const
        {
            return escape_size;
        }

        void ResetSize()
        {
            size = 0;
            escape_size = 0;
        }

        void AddLine()
        {
            line++;
            column = 1;
        }

        void AddColumn()
        {
            column++;
        }

        void AddSize()
        {
            size++;
        }

        void AddEscapeSize()
        {
            escape_size++;
        }

        void SetTokenPosition(
            const Celery::Trait::VeryLarge& line,
            const Celery::Trait::VeryLarge& column
        )
        {
            token_line = line;
            token_column = column;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetTokenLine() const
        {
            return token_line;
        }

        [[nodiscard]] Celery::Trait::VeryLarge GetTokenColumn() const
        {
            return token_column;
        }
    };
}