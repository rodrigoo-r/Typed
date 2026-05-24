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

namespace Typed::Support::Stream
{
    template <
        typename T,
        typename Adapter = ADT::Stream::External<T>
    >
    T &SafePeek(Adapter &adapter)
    {
        // Special case: Empty stream
        if (adapter.Empty())
        {
            throw ADT::Exception::OutOfBounds(1, 1);
        }

        // If the adapter doesn't have more elements
        if (!adapter.HasNext())
        {
            throw ADT::Exception::OutOfBounds(
                adapter.Curr().line,
                adapter.Curr().column
            );
        }

        return adapter.Peek();
    }
}