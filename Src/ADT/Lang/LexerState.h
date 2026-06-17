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

#include <cstddef>

#include "EscapeType.h"

namespace Typed::ADT::Lang
{
    class LexerState
    {
        bool string_literal = false;
        bool multi_line_string_literal = false;
        bool number_literal = false;
        bool float_literal = false;
        bool identifier = false;
        size_t start = 0;
        size_t line = 1;
        size_t column = 1;
        size_t size = 0;
        size_t token_line = 1;
        size_t token_column = 1;
        EscapeType escape_type = EscapeType::NoEscape;

    public:
        void Reset()
        {
            string_literal = false;
            number_literal = false;
            float_literal = false;
            identifier = false;
            multi_line_string_literal = false;
            escape_type = EscapeType::NoEscape;
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

        [[nodiscard]] bool IsMultiLineStringLiteral() const
        {
            return multi_line_string_literal;
        }

        void ToggleIdentifier()
        {
            identifier = !identifier;
        }

        void ToggleStringLiteral()
        {
            string_literal = !string_literal;
        }

        void ToggleMultiLineStringLiteral()
        {
            multi_line_string_literal = !multi_line_string_literal;
        }

        void ToggleNumberLiteral()
        {
            number_literal = !number_literal;
        }

        void ToggleFloatLiteral()
        {
            float_literal = !float_literal;
        }

        void SetStart(const size_t &start)
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

        [[nodiscard]] size_t GetStart() const
        {
            return start;
        }

        [[nodiscard]] size_t GetLine() const
        {
            return line;
        }

        [[nodiscard]] size_t GetColumn() const
        {
            return column;
        }

        [[nodiscard]] size_t GetSize() const
        {
            return size;
        }

        void ResetSize()
        {
            size = 0;
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

        void SetTokenPosition(
            const size_t& line,
            const size_t& column
        )
        {
            token_line = line;
            token_column = column;
        }

        [[nodiscard]] size_t GetTokenLine() const
        {
            return token_line;
        }

        [[nodiscard]] size_t GetTokenColumn() const
        {
            return token_column;
        }
    };
}