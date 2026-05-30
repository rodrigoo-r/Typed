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
// Created by Rodrigo on 5/30/26.
//

#include "ADT/List/Object.h"

#include "RadiansToDegrees.h"

#include "Support/Math/CalculateDegrees.h"
#include "Support/Runtime/GetObjValue.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Math;

ADT::Runtime::Object Math::RadiansToDegrees(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];

    if (obj.type == ADT::Runtime::ObjectType::Float)
    {
        auto &val = Support::Runtime::GetFloatObj(obj);
        return {
            ADT::Runtime::ObjectType::Float,
            Support::Math::RadiansToDegrees(val)
        };
    }

    if (obj.type == ADT::Runtime::ObjectType::Integer)
    {
        auto &val = Support::Runtime::GetIntObj(obj);
        return {
            ADT::Runtime::ObjectType::Float,
            Support::Math::RadiansToDegrees(val)
        };
    }

    throw ADT::Exception::MismatchedType(
        trace->line,
        trace->column
    );
}
