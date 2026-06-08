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
#include "SafePeek.h"

namespace Typed::Support::Stream
{
    auto &SafeNext(auto &adapter)
    {
        auto &peek = SafePeek(adapter);
        adapter.Next();

        return peek;
    }

    auto &SafeNext(auto &adapter, auto &trace)
    {
        auto &peek = SafePeek(adapter, trace);
        adapter.Next();

        return peek;
    }
}