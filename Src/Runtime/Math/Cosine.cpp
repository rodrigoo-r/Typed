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

#include "ADT/List/Object.h"

#include "Cosine.h"

#include "ADT/Exception/MismatchedType.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Math;

ADT::Runtime::Object Math::Cosine(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &target = args[0];
    if (target.type == ADT::Runtime::ObjectType::Float)
    {
        auto &val = Support::Runtime::GetFloatObj(target);
        return {
            ADT::Runtime::ObjectType::Float,
            std::cos(val)
        };
    }

    if (target.type == ADT::Runtime::ObjectType::Integer)
    {
        auto &val = Support::Runtime::GetIntObj(target);
        return {
            ADT::Runtime::ObjectType::Float,
            std::cos(static_cast<float>(val))
        };
    }

    throw ADT::Exception::MismatchedType(
        trace->line,
        trace->column
    );
}