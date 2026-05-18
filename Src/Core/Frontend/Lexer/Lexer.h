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

namespace Typed::Core::Frontend::Lexer
{
    class Machine
    {
    protected:
        ADT::Stream::Token Tokens;

        void Comment();

    public:
        using EntryRef =
            Celery::Array::Stream<char> &;

        using ConstStreamRef =
            const ADT::Stream::Token&;

    private:

        EntryRef Contents;

    public:
        Machine(EntryRef contents) :
            Contents(contents)
        {}

        ConstStreamRef Lex(const Celery::Str::String &input);
    };
}