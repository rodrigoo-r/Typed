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

void Failable::Failable::PrintConsiderations()
{
    std::cout << std::endl;

    std::cout
        << Ansi::Bold::Bright::Magenta
        << "note: "
        << Ansi::Reset
        << "if you believe this is a mistake, please open an issue at:"
    << std::endl
        << Ansi::Bold::Bright::Cyan
        << "  https://github.com/rodrigoo-r/Typed/issues"
        << Ansi::Reset
    << std::endl;
}