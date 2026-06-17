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
        class T,
        class Stream = ADT::Stream::External<T>,
        typename Equal = ADT::Equality::Agnostic
    >
    void Expect(Stream &stream, auto expected)
    {
        auto &element = SafeNext(stream);
        if (!Equal::Equals(element, expected))
        {
            throw ADT::Exception::UnexpectedToken(
                element.line,
                element.column
            );
        }
    }
}