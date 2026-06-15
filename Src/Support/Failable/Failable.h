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

#include "ADT/Exception/Traceable.h"
#include "ADT/Stream/File.h"

namespace Typed::Support::Failable
{
    class Failable
    {
        static inline ADT::Stream::FileView contents;

        static void PrintMessage(const char *message);
        static void PrintConsiderations();
        static void Fail(ADT::Exception::Traceable &traceable);
        static void Fail(std::exception &except);

    public:
        static void Setup(ADT::Stream::File &file)
        {
            contents = ADT::Stream::FileView{file.Ptr(), file.Size()};
        }

        template <
            typename Obj,
            typename Ret,
            typename... Args,
            typename... CallArgs
        >
        static decltype(auto) Try(Ret (Obj::*method)(Args...), Obj& obj, CallArgs&&... args)
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
                Fail(except);
                exit(1);
            }
        }

        template <
            typename Function,
            typename... Args
        >
        static decltype(auto) TryAlwaysTraceable(
            auto *trace,
            Function &function,
            Args&&... args
        )
        {
            try
            {
                return function(std::forward<Args>(args)...);
            } catch (ADT::Exception::Traceable &traceable)
            {
                Fail(traceable);
                exit(1);
            } catch (std::exception &except)
            {
                ADT::Exception::Traceable traceable(
                    except.what(),
                    trace->line,
                    trace->column
                );

                Fail(traceable);
                exit(1);
            }
        }
    };
}