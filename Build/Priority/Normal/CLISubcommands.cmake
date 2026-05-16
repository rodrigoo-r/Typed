#-----------------------------------------------------#
#                                                     #
#                           Typed                     #
#                   A text formatting DSL             #
#                                                     #
#-----------------------------------------------------#
#                                                     #
#         Created by Rodrigo R. & Contributors        #
#         Released under the Apache License 2.0       #
#            Check LICENSE.MD for more info           #
#                                                     #
#-----------------------------------------------------#

include(${Helper_Dir}/File/GeneratedFileTemplate.cmake)
include(${Helper_Dir}/String/CapitalizeFirst.cmake)

# Define the contents of the file we're going to generate
Get_Generated_File_Template(Cli_Subcommands_Contents)

string(APPEND Cli_Subcommands_Contents "#define TYPED_CLI_SUBCOMMANDS \\\n")
set(Cli_Subcommand_Process "#define TYPED_CLI_SUBCOMMANDS_PROCESS \\\n")

# Read the flags
file(
        GLOB
        Cli_Subcommands_Files
        RELATIVE
        ${Black_Magic_Dir}/CLI/Subcommands
        ${Black_Magic_Dir}/CLI/Subcommands/*
)

foreach (Subcommand IN LISTS Cli_Subcommands_Files)
    # Read the content of the subcommand file
    file(READ "${Black_Magic_Dir}/CLI/Subcommands/${Subcommand}" Subcommand_Description)

    # Get the filename without the extension
    get_filename_component(Subcommand_Name "${Subcommand}" NAME_WE)

    # Capitalize the first letter of the subcommand name
    Capitalize_First(Subcommand_Name Subcommand_Name_Capitalized)

    # Convert the name to lowercase
    string(TOLOWER "${Subcommand_Name}" Subcommand_Name)

    # Construct the subcommand definition
    set(Subcommand_Definition "${Subcommand_Name}")
    string(
            APPEND
            Cli_Subcommands_Contents
            "    auto ${Subcommand_Name} = app.add_subcommand(\"${Subcommand_Definition}\", \"${Subcommand_Description}\"); \\\n"
    )

    string(
            APPEND
            Cli_Subcommands_Contents
            "    std::string ${Subcommand_Name}_Contents; \\\n"
    )

    string(
            APPEND
            Cli_Subcommands_Contents
            "    ${Subcommand_Name}->add_option(\"item\", ${Subcommand_Name}_Contents)->required(); \\\n"
    )

    string(
            APPEND
            Cli_Subcommand_Process
            "    if (*${Subcommand_Name}) { \\\n"
            "       Typed::Terminal::Subcommand::"
            "${Subcommand_Name_Capitalized}(${Subcommand_Name}_Contents); \\\n"
            "       return 0; \\\n"
            "    } \\\n"
    )
endforeach ()

# Write an empty newline at the end of the macro definition
string(APPEND Cli_Subcommands_Contents "\n")
string(APPEND Cli_Subcommand_Process "\n")

string(APPEND Cli_Subcommands_Contents "${Cli_Subcommand_Process}")

# Write the contents to the output file
file(
        WRITE
        "${Generated_Dir}/CliSubcommands.h"
        "${Cli_Subcommands_Contents}"
)