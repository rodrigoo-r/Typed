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
// Created by Rodrigo on 5/20/26.
//

#include "ADT/Exception/UnknownEntryPoint.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void Walker::Walk()
{
    // Get the main procedure
    auto main = runnable.procedures.find("Main");
    if (main == runnable.procedures.end())
        throw ADT::Exception::UnknownEntryPoint();

    // Run the main procedure
    VariableMap args{};
    Procedure(main->second, args, nullptr);
}
