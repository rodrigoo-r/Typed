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
// Created by Rodrigo on 5/24/26.
//

#include "ADT/List/Object.h"
#include "Size.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Size(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    if (obj.type != ADT::Runtime::ObjectType::String)
    {
        auto &str = Support::Runtime::GetStrObj(obj);
        return {
            ADT::Runtime::ObjectType::Integer,
            (int)str.Size()
        };
    }

    auto &str = Support::Runtime::GetOwnedStrObj(obj);
    return {
        ADT::Runtime::ObjectType::Integer,
        (int)str.Size()
    };
}