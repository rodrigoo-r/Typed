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

        // Loops
        For,
        While,

        // Delimiters
        Begin,
        EndProcedure,
        EndFor,
        EndWhile,
        EndIf,
        EndCall,
        As,
        With,
        Arguments,
        To,
        Step,
        Do,
        In,
        By,
        From,
        Returns,
        Then,

        // Boolean operations
        If,
        Else,
        ElseIf,
        And,
        Or,
        Not,
        Equal,
        Greater,
        Less,
        GreaterEqual,
        LessEqual,
        NotEqual,

        // Instructions
        Declare,
        Call,
        Add,
        Sub,
        Mul,
        Div,
        Return,

        // Data types
        String,
        Float,
        Integer,
        Boolean,
        List,
        Dictionary,
        Regex,

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