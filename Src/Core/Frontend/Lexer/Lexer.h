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

#pragma once

#include "ADT/Lang/LexerState.h"
#include "ADT/Stream/File.h"
#include "ADT/Stream/Token.h"

namespace Typed::Core::Frontend::Lexer
{
    class Machine
    {
    protected:
        ADT::Stream::Token tokens;
        ADT::Lang::LexerState state;

        void Flush();
        void Comment();

    public:
        using EntryRef =
            ADT::Stream::File &;

        using StreamRef =
            ADT::Stream::Token&;

    private:

        EntryRef contents;

    public:
        Machine(EntryRef contents) :
            contents(contents)
        {}

        StreamRef Lex();
    };
}