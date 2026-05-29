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
// Created by Rodrigo on 5/29/26.
//

#pragma once
#include <Celery/String/String.h>
#include <re2/re2.h>

#include "ADT/Memory/HeapRef.h"

namespace Typed::ADT::Regex
{
    class Ref
    {
    public:
        using Pattern =
            RE2;

        using PatternRef =
            Memory::HeapRef<Pattern>;

    private:
        PatternRef pattern;

    public:
        Ref()
            : pattern(nullptr)
        {}

        void Build(Celery::Str::String &p)
        {
            pattern = PatternRef::Make(p.CStr());
        }

        auto &GetPattern()
        {
            return pattern;
        }
    };
}
