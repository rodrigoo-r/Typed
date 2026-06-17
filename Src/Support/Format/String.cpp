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

#include "String.h"

#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::String(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto val = Runtime::AccessString(obj);
    adapter.append(val.data(), val.size());
}

template
void Format::String(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::String(
    ADT::Runtime::Object &,
    std::string &
);