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

namespace Typed::Support::Stream
{
    auto &SafePeek(auto &adapter, auto &trace)
    {
        // Special case: Empty stream
        if (adapter.Empty())
        {
            throw ADT::Exception::OutOfBounds(1, 1);
        }

        // If the adapter doesn't have more elements
        if (!adapter.HasNext())
        {
            if constexpr (std::is_pointer_v<std::decay_t<decltype(trace)>>)
            {
                throw ADT::Exception::OutOfBounds(
                    trace->line,
                    trace->column
                );
            }
            else
            {
                throw ADT::Exception::OutOfBounds(
                    trace.line,
                    trace.column
                );
            }
        }

        return adapter.Peek();
    }

    auto &SafePeek(auto &adapter)
    {
        if (adapter.Empty())
        {
            throw ADT::Exception::OutOfBounds(1, 1);
        }
        
        if (adapter.Pos() == 0)
        {
            return SafePeek(adapter, adapter.Peek());
        }

        return SafePeek(adapter, adapter.Curr());
    }
}