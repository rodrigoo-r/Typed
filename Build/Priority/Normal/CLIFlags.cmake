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
Get_Generated_File_Template(Cli_Flags_Contents)

string(APPEND Cli_Flags_Contents "#define TYPED_CLI_FLAGS \\\n")

# Read the flags
file(
        GLOB
        Cli_Flags_Files
        RELATIVE
        ${Black_Magic_Dir}/CLI/Flags
        ${Black_Magic_Dir}/CLI/Flags/*
)

foreach (Level_Name IN LISTS Cli_Flags_Files)
    # Read the files in the current level
    file(GLOB Level_Files "${Black_Magic_Dir}/CLI/Flags/${Level_Name}/*.txt")

    foreach (Flag_File IN LISTS Level_Files)
        # Read the content of the flag file
        file(READ "${Flag_File}" Flag_Description)

        # Get the filename without the extension
        get_filename_component(Flag_Name "${Flag_File}" NAME_WE)

        # Capitalize the first letter of the flag name
        Capitalize_First(Flag_Name Flag_Name_Capitalized)

        # Convert the name to lowercase
        string(TOLOWER "${Flag_Name}" Flag_Name)

        # Get the first character of the flag name
        string(SUBSTRING "${Flag_Name}" 0 1 Flag_First_Char)

        # Construct the flag denomination
        set(Flag_Definition "-${Flag_First_Char},--${Flag_Name}")
        string(
                APPEND
                Cli_Flags_Contents
                "    app.add_flag(\"${Flag_Definition}\", "
                "Config::${Level_Name}::Show${Flag_Name_Capitalized}, "
                "\"${Flag_Description}\"); \\\n"
        )
    endforeach ()
endforeach()

# Write an empty newline at the end of the macro definition
string(APPEND Cli_Flags_Contents "\n")

# Write the contents to the generated file
set(Cli_Flags_File_Path "${Generated_Dir}/CliFlags.h")
file(WRITE "${Cli_Flags_File_Path}" "${Cli_Flags_Contents}")