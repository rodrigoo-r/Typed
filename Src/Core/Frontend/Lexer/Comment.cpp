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
// Created by Rodrigo on 5/17/26.
//

#include "Lexer.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Lexer;

void Machine::Comment()
{
    auto ptr = Contents.Ptr() + Contents.Pos();
    auto end = ptr + Contents.Size();

    // Find the next newline
    auto newline = std::find(ptr, end, '\n');
    if (newline != end)
    {
        // Move the contents position to the character after the newline
        Contents.SetPos(Contents.Pos() + (newline - ptr) + 1);
    }
    else
    {
        // Move the contents position to the end of the stream
        Contents.SetPos(Contents.Size());
    }
}
