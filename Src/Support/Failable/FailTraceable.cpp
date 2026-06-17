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


#include "ADT/Exception/Traceable.h"
#include "Failable.h"
#include "Support/Ansi/Ansi.h"
#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Support;

void PrintSpaces(
    size_t line,
    size_t column
)
{
    // Print spaces for the separator
    std::cout << "  ";

    // Print as many blank spaces as digits in the line
    while (line > 0)
    {
        std::cout << " ";
        line /= 10;
    }

    for (auto i = 0; i < column; i++)
    {
        std::cout << " ";
    }
}

void Failable::Failable::Fail(
    ADT::Exception::Traceable &traceable
)
{
    PrintMessage(traceable.what());
    std::cout
        << Ansi::White
        << "│"
        << Ansi::Reset
        << Ansi::Italic::White
        << "  └─ at "
        << Ansi::Reset
        << Ansi::Bright::Italic::Blue
        << traceable.line
        << Ansi::Reset
        << Ansi::Italic::White
        << ":"
        << Ansi::Reset
        << Ansi::Bright::Italic::Magenta
        << traceable.column
        << Ansi::Reset
    << std::endl;

    std::cout
        << Ansi::White
        << "│"
        << Ansi::Reset
    << std::endl;

    std::cout
        << Ansi::White
        << traceable.line
        << " │ "
        << Ansi::Reset
    ;

    // Find the exact line where the error happens
    size_t line_counter = 1;
    auto ptr = contents.data();
    auto end = ptr + contents.size();

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
    std::string_view line_view(ptr, end - ptr);
    std::cout <<
        Ansi::White <<
        line_view <<
        Ansi::Reset
    << std::endl;

    PrintSpaces(traceable.line, traceable.column);
    std::cout <<
        Ansi::Bright::Red <<
        "^" <<
        Ansi::Reset
    << std::endl;

    PrintSpaces(traceable.line, traceable.column);
    std::cout <<
        Ansi::Bright::Red <<
        "here!" <<
        Ansi::Reset
    << std::endl;

    PrintConsiderations();
}