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

#pragma once

#include "ADT/Stream/File.h"

namespace Typed::Support::Failable
{
    class Failable
    {
        ADT::Stream::File &contents;

        void PrintMessage(const char *message);
        void Fail(ADT::Exception::Traceable &traceable);
        void Fail(std::exception &except);

    public:
        Failable(ADT::Stream::File &contents) :
            contents(contents) {}

        template <
            typename Obj,
            typename Ret,
            typename... Args,
            typename... CallArgs
        >
        decltype(auto) Try(Ret (Obj::*method)(Args...), Obj& obj, CallArgs&&... args)
        {
            try
            {
                return (obj.*method)(std::forward<CallArgs>(args)...);
            } catch (ADT::Exception::Traceable &traceable)
            {
                Fail(traceable);
                exit(1);
            } catch (std::exception &except)
            {
                exit(1);
            }
        }
    };
}