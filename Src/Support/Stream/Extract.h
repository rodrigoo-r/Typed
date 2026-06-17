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
// Created by Rodrigo on 5/19/26.
//

#pragma once
#include "ADT/Equality/Agnostic.h"
#include "ADT/Exception/UnexpectedToken.h"
#include "ADT/Stream/External.h"
#include "SafeNext.h"

namespace Typed::Support::Stream
{
    template <
        typename T,
        typename Eq = ADT::Equality::Agnostic
    >
    ADT::Stream::External<T> Extract(
        ADT::Array::Stream<T> &stream,
        auto Dest
    )
    {
        auto start = stream.Pos();
        bool met_delim = false;
        size_t size = 0;

        // Build the stream 1 element at a time
        while (stream.HasNext())
        {
            auto &next = SafeNext(stream);
            if (Eq::Equals(next, Dest))
            {
                met_delim = true;
                break;
            }

            size++;
        }

        if (!met_delim)
        {
            throw ADT::Exception::UnexpectedToken(
                stream.Curr().line,
                stream.Curr().column
            );
        }

        // Return the view
        return {
            stream.data() + start,
            size
        };
    }
}