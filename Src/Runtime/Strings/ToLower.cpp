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
    ADT::Lang::AST *_
)
{
    auto str = Support::Runtime::AccessString(args[0]);
    std::string result;

    // Resize the result
    result.reserve(str.size());

    // Write the string
    for (char c : str)
    {
        result.push_back(std::tolower(c));
    }

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}