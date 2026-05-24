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
#include "ADT/Exception/OutOfBounds.h"
#include "ADT/Stream/External.h"
#include "SafePeek.h"

namespace Typed::Support::Stream
{
    template <
        typename T,
        typename Adapter = ADT::Stream::External<T>
    >
    T &SafeNext(Adapter &adapter)
    {
        auto &peek = SafePeek<T, Adapter>(adapter);
        adapter.Next();

        return peek;
    }
}