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
// Created by Rodrigo on 5/26/26.
//

#include "ADT/List/Object.h"
#include "ToUpper.h"

#include "FindIndex.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::ToUpper(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    Celery::Str::String result;

    // Resize the result
    result.ResizeFill(str.Size(), ' ');

    // Write the string
    for (auto i = 0; i < str.Size(); i++)
    {
        auto c = str[i];
        result[i] = std::toupper(c);
    }

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}