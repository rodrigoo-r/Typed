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
// Created by Rodrigo on 5/27/26.
//

#include "Dictionary.h"

#include <Celery/Io/Stream.h>

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"
#include "Object.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Dictionary(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto &val = Runtime::GetDictionaryObj(obj);

    adapter.Write("Dictionary(", 11);

    auto last = val->size() - 1;
    Celery::Trait::VeryLarge i = 0;

    for (auto &pair : *val)
    {
        Object(pair.first, adapter);
        adapter.Write(" : ", 3);
        Object(pair.second, adapter);

        if (i != last)
        {
            adapter.Write(", ", 2);
        }

        i++;
    }

    adapter.Write(')');
}

template
void Format::Dictionary(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Dictionary(
    ADT::Runtime::Object &,
    Celery::Str::String &
);
