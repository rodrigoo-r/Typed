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

#include "Float.h"

#include <Celery/Algo/Ftoa.h>

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Float(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto &val = Runtime::GetFloatObj(obj);
    Celery::Algorithm::Ftoa(val, adapter);
}

template
void Format::Float(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Float(
    ADT::Runtime::Object &,
    Celery::Str::String &
);
