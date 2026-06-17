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
// Created by Rodrigo on 5/30/26.
//

#include "Failable.h"
#include "Support/Ansi/Ansi.h"

using namespace Typed;
using namespace Typed::Support;

void Failable::Failable::PrintMessage(const char *message)
{
    std::cout
        << Ansi::Bold::Bright::Red
        << "error: "
        << Ansi::Reset
        << message
    << std::endl;
}