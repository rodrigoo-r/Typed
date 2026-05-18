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

namespace Typed::ADT::Lang
{
    enum class TokenType
    {
        // Import keywords
        Use,

        // Definitions
        Procedure,

        // Delimiters
        Begin,
        EndProcedure,
        As,
        With,
        Arguments,
        To,
        By,

        // Instructions
        Declare,
        Call,
        CallMethod,
        Add,
        Sub,
        Mul,
        Div,

        // Literals
        StringLiteral,
        NumberLiteral,
        FloatLiteral,
        TrueLiteral,
        FalseLiteral,

        // Punctuation
        Semicolon,
        Comma,

        Identifier,
        Unknown
    };
}