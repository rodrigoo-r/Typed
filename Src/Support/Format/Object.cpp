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

#include "Object.h"

#include "ADT/Runtime/Object.h"

#include "ADT/Stdout/Wrapper.h"
#include "Boolean.h"
#include "Dictionary.h"
#include "Float.h"
#include "Integer.h"
#include "List.h"
#include "String.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Object(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    switch (obj.type)
    {
        case ADT::Runtime::ObjectType::String:
        {
            String(obj, adapter);
            break;
        }

        case ADT::Runtime::ObjectType::Float:
        {
            Float(obj, adapter);
            break;
        }

        case ADT::Runtime::ObjectType::Integer:
        {
            Integer(obj, adapter);
            break;
        }

        case ADT::Runtime::ObjectType::Boolean:
        {
            Boolean(obj, adapter);
            break;
        }

        case ADT::Runtime::ObjectType::List:
        {
            List(obj, adapter);
            break;
        }

        case ADT::Runtime::ObjectType::Dictionary:
        {
            Dictionary(obj, adapter);
            break;
        }

        default: break;
    }
}

template
void Format::Object(
    ADT::Runtime::Object &obj,
    std::string &adapter
);

template
void Format::Object(
    ADT::Runtime::Object &obj,
    ADT::Stdout::Wrapper &adapter
);
