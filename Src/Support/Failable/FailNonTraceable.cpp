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

void Failable::Failable::Fail(
    std::exception &traceable
)
{
    PrintMessage(traceable.what());

    Celery::Io::Println(
        Celery::Misc::Ansi::White,
        "└── this exception is not traceable",
        Celery::Misc::Ansi::Reset
    );

    PrintConsiderations();
}