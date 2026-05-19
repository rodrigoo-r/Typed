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
// Created by Rodrigo on 5/19/26.
//

#pragma once

namespace Typed::ADT::Bytecode
{
    enum class InstructionType
    {
        // Memory
        Push,   // Declares a variable
        Pull,   // Gets a variable from the stack

        // Raw instructions
        Call,   // Call a procedure
        Offset, // Get an offset from a ptr
        Add,    // Performs a sum to a variable
        Sub,    // Performs a subtraction to a variable
        Div,    // Performs a multiplication to a variable
        Mul,    // Performs a division to a variable
    };
}