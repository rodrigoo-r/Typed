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


#include "ADT/Exception/Traceable.h"
#include "Failable.h"
#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Support;

void PrintSpaces(
    Celery::Trait::VeryLarge line,
    Celery::Trait::VeryLarge column
)
{
    // Print spaces for the separator
    Celery::Io::Print("  ");

    // Print as many blank spaces as digits in the line
    while (line > 0)
    {
        Celery::Io::Print(" ");
        line /= 10;
    }

    for (auto i = 0; i < column; i++)
    {
        Celery::Io::Print(" ");
    }
}

void Failable::Failable::Fail(
    ADT::Exception::Traceable &traceable
)
{
    PrintMessage(traceable.what());
    Celery::Io::Println(
        Celery::Misc::Ansi::White,
        "│",
        Celery::Misc::Ansi::Reset,
        Celery::Misc::Ansi::Italic::White,
        "  └─ at ",
        Celery::Misc::Ansi::Reset,
        Celery::Misc::Ansi::Bright::Italic::Blue,
        traceable.line,
        Celery::Misc::Ansi::Reset,
        Celery::Misc::Ansi::Italic::White,
        ":",
        Celery::Misc::Ansi::Reset,
        Celery::Misc::Ansi::Bright::Italic::Magenta,
        traceable.column,
        Celery::Misc::Ansi::Reset
    );

    Celery::Io::Println(
        Celery::Misc::Ansi::White,
        "│",
        Celery::Misc::Ansi::Reset
    );

    Celery::Io::Print(
        Celery::Misc::Ansi::White,
        traceable.line,
        " │ ",
        Celery::Misc::Ansi::Reset
    );

    // Find the exact line where the error happens
    Celery::Trait::VeryLarge line_counter = 1;
    auto ptr = contents.Ptr();
    auto end = ptr + contents.Size();

    while (line_counter < traceable.line)
    {
        auto newline = std::find(ptr, end, '\n');
        ptr = newline + 1;
        line_counter++;
    }

    // Find the new end of the file, either another newline or EOF
    auto new_end = std::find(ptr, end, '\n');
    if (new_end == end)
    {
        end = new_end + 1;
    } else
    {
        end = new_end;
    }

    // Create a string view for the line
    Celery::Str::External line_view(ptr, end - ptr);
    Celery::Io::Println(
        Celery::Misc::Ansi::White,
        line_view,
        Celery::Misc::Ansi::Reset
    );

    PrintSpaces(traceable.line, traceable.column);
    Celery::Io::Println(
        Celery::Misc::Ansi::Bright::Red,
        "^",
        Celery::Misc::Ansi::Reset
    );

    PrintSpaces(traceable.line, traceable.column);
    Celery::Io::Println(
        Celery::Misc::Ansi::Bright::Red,
        "here!",
        Celery::Misc::Ansi::Reset
    );

    PrintConsiderations();
}