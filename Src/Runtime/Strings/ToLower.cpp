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
#include "ToLower.h"

#include "FindIndex.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::ToLower(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto str = Support::Runtime::AccessString(args[0]);
    Celery::Str::String result;

    // Resize the result
    result.ResizeFill(str.Size(), ' ');

    // Write the string
    for (auto i = 0; i < str.Size(); i++)
    {
        auto c = str[i];
        result[i] = std::tolower(c);
    }

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}