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

#include "Config/Core.h"
#include "Generated/CliFlags.h"
#include "Generated/CliSubcommands.h"
#include "Subcommand/Run/Handler.h"

int Typed::Terminal::Run(const int argc, char **argv)
{
    CLI::App app{};

    // Add flags and subcommands
    TYPED_CLI_FLAGS;
    TYPED_CLI_SUBCOMMANDS;

    // Parse CLI input
    CLI11_PARSE(app, argc, argv);

    // Runs the subcommand selected by the user
    TYPED_CLI_SUBCOMMANDS_PROCESS;

    return 0;
}