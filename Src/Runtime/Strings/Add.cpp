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
#include "Add.h"

#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Add(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    auto target = Support::Runtime::AccessString(obj);
    auto &str_obj = args[1];
    auto request_str = Support::Runtime::AccessString(str_obj);
    char *ptr = target.Ptr();
    Celery::Trait::VeryLarge size = target.Size();

    if (!std::holds_alternative<Celery::Str::String>(obj.value))
    {
        obj.value = Celery::Str::String(ptr, size);
    }

    ptr = request_str.Ptr();
    size = request_str.Size();

    // Add the value to the string
    auto &str = Support::Runtime::GetOwnedStrObj(obj);
    str.Write(ptr, size);

    return obj;
}