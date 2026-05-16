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
// Created by Rodrigo on 5/15/26.
//

#include "EntryPoint.h"

#include <CLI/CLI.hpp>

int Typed::Terminal::Run(const int argc, char **argv)
{
    CLI::App app{TYPED_PROJECT_NAME};
    CLI11_PARSE(app, argc, argv);
    
    return 0;
}
