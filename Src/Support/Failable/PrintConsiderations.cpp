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

#include <Celery/Misc/Ansi.h>

#include "Failable.h"
#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Support;

void Failable::Failable::PrintConsiderations()
{
    Celery::Io::Println();

    Celery::Io::Println(
        Celery::Misc::Ansi::Bold::Bright::Magenta,
        "note: ",
        Celery::Misc::Ansi::Reset,
        "if you believe this is a mistake, please open an issue at:"
    );

    Celery::Io::Println(
        Celery::Misc::Ansi::Bold::Bright::Cyan,
        "  https://github.com/rodrigoo-r/Typed/issues",
        Celery::Misc::Ansi::Reset
    );
}