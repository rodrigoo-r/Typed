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

    adapter.append("Dictionary(", 11);

    auto last = val->size() - 1;
    size_t i = 0;

    for (auto &pair : *val)
    {
        Object(pair.first, adapter);
        adapter.append(" : ", 3);
        Object(pair.second, adapter);

        if (i != last)
        {
            adapter.append(", ", 2);
        }

        i++;
    }

    adapter.append(")", 1);
}

template
void Format::Dictionary(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Dictionary(
    ADT::Runtime::Object &,
    std::string &
);
