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
#include <Celery/String/String.h>


#include "ADT/Stream/Token.h"
#include "State.h"

namespace Typed::Core::Frontend::Lexer
{
    class Machine
    {
    protected:
        ADT::Stream::Token tokens;
        State state;

        void Comment();

    public:
        using EntryRef =
            Celery::Array::Stream<char> &;

        using ConstStreamRef =
            const ADT::Stream::Token&;

    private:

        EntryRef contents;

    public:
        Machine(EntryRef contents) :
            contents(contents)
        {}

        ConstStreamRef Lex();
    };
}