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
// Created by Rodrigo on 5/16/26.
//

#include "Handler.h"

#include <Celery/Io/Io.h>
#include <magic_enum/magic_enum.hpp>

#include "Core/Frontend/Lexer/Lexer.h"
#include "Core/Frontend/Parser/Parser.h"
#include "Support/File/Reader.h"
#include "Support/Printer/ASTPrinter.h"

using namespace Typed;
using namespace Typed::Terminal;

void Subcommand::Run(const std::string &input)
{
    Support::File::Reader reader;
    reader.SetPath({input.data(), input.size()});

    auto contents = reader.Read();
    Core::Frontend::Lexer::Machine lexer(contents);
    auto &tokens = lexer.Lex();

    Core::Frontend::Parser::Machine parser(tokens);
    auto root = parser.Parse();
    Support::Printer::ASTPrinter printer(root);
    printer.Print();

}
