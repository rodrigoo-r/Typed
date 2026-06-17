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

#include "Boolean.h"

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Boolean(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto &val = Runtime::GetBoolObj(obj);
    if (val)
    {
        adapter.append("True", 4);
        return;
    }

    adapter.append("False", 5);
}

template
void Format::Boolean(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Boolean(
    ADT::Runtime::Object &,
    std::string &
);
