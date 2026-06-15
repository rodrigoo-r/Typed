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

#include "Core/Backend/Walker.h"
#include "Core/Frontend/Lexer/Lexer.h"
#include "Core/Frontend/Parser/Parser.h"
#include "Core/MiddleEnd/PreWalker.h"
#include "Support/Failable/Failable.h"
#include "Support/File/Reader.h"

using namespace Typed;
using namespace Typed::Terminal;

void Subcommand::Run(const std::string &input)
{
    Support::File::Reader reader;
    reader.SetPath({input.data(), input.size()});

    auto contents =
        Support::Failable::Failable::Try(
            &Support::File::Reader::Read,
            reader
        );

    Support::Failable::Failable::Setup(contents);

    Core::Frontend::Lexer::Machine lexer(contents);

    auto &tokens = Support::Failable::Failable::Try(
        &Core::Frontend::Lexer::Machine::Lex,
        lexer
    );

    contents.ClearEscapeIdx();

    Core::Frontend::Parser::Machine parser(tokens);
    auto root = Support::Failable::Failable::Try(
        &Core::Frontend::Parser::Machine::Parse,
        parser
    );

    // Deallocate tokens' memory, freeing contents
    tokens.Reset();

    Core::MiddleEnd::PreWalker pre_walker(root);
    auto &file = Support::Failable::Failable::Try(
        &Core::MiddleEnd::PreWalker::Process,
        pre_walker
    );

    // Run the code
    Core::Backend::Walker walker(file);
    Support::Failable::Failable::Try(
        &Core::Backend::Walker::Walk,
        walker
    );
}
