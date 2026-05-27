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

#include "List.h"

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"
#include "Object.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::List(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    adapter.Write("List(", 5);
    auto &val = Runtime::GetListObj(obj);
    if (val->Empty())
    {
        adapter.Write(')');
        return;
    }

    auto last = val->Size() - 1;
    for (auto i = 0; i < val->Size(); i++)
    {
        auto &el = (*val)[i];
        Object(el, adapter);

        if (i != last)
            adapter.Write(", ", 2);
    }

    adapter.Write(')');
}

template
void Format::List(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::List(
    ADT::Runtime::Object &,
    Celery::Str::String &
);