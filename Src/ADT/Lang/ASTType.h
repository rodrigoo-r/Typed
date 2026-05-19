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
// Created by Rodrigo on 5/18/26.
//

#pragma once

namespace Typed::ADT::Lang
{
    enum class ASTType
    {
        // Root
        Root,

        // Top-level declarations
        Use,
        Procedure,
        Arguments,
        Argument,
        Body,

        // Data Types
        String,
        Integer,
        Float,
        Boolean,

        // Expression
        Expression,

        // Instructions
        Call,
        CallMethod,
        Add,
        Sub,
        Div,
        Mul,

        // Declarations
        Declare,

        // Literals
        StringLiteral,
        NumberLiteral,
        FloatLiteral,
        TrueLiteral,
        FalseLiteral,

        // Identifier
        Identifier
    };
}