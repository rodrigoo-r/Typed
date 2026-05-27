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

#include "Integer.h"

#include <Celery/Algo/Itoa.h>

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Integer(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto &val = Runtime::GetIntObj(obj);
    Celery::Algorithm::Itoa(val, adapter);
}

template
void Format::Integer(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Integer(
    ADT::Runtime::Object &,
    Celery::Str::String &
);
