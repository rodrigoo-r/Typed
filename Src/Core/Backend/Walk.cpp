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
#include "ADT/Exception/UnknownLibrary.h"
#include "Support/Runtime/LibraryMap.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void Walker::Walk()
{
    // Add imported libraries
    for (auto &lib_name : runnable.imports)
    {
        auto pkg = Support::Runtime::LibraryMap.find(lib_name);
        if (pkg == Support::Runtime::LibraryMap.end())
            throw ADT::Exception::UnknownLibrary(lib_name);

        // Add all procedures imported
        for (auto &[name, proc] : pkg->second)
        {
            runnable.procedures.emplace(name, proc);
        }
    }

    // Get the main procedure
    auto main = runnable.procedures.find("Main");
    if (main == runnable.procedures.end())
        throw ADT::Exception::UnknownEntryPoint();

    // Run the main procedure
    ADT::List::Object args;
    Procedure(main->second, args, nullptr);
}
