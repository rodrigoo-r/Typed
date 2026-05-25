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

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Add(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    auto &str_obj = args[1];
    char *ptr = nullptr;
    Celery::Trait::VeryLarge size = 0;

    // Get the value from the object
    if (obj.type == ADT::Runtime::ObjectType::String)
    {
        auto &str = Support::Runtime::GetStrObj(obj);
        ptr = str.Ptr();
        size = str.Size();
    } else
    {
        auto &str = Support::Runtime::GetOwnedStrObj(obj);
        ptr = str.Ptr();
        size = str.Size();
    }

    if (obj.type != ADT::Runtime::ObjectType::OwnedString)
    {
        auto &str = Support::Runtime::GetStrObj(str_obj);
        obj.type = ADT::Runtime::ObjectType::OwnedString;
        obj.value = Celery::Str::String(str.Ptr(), str.Size());
    }

    // Add the value to the string
    auto &str = Support::Runtime::GetOwnedStrObj(obj);
    str.Write(ptr, size);

    return {};
}