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
// Created by Rodrigo on 5/29/26.
//

#include "MatchesPartly.h"

#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"
#include "Support/Runtime/GetObjValue.h"
#include "Support/Runtime/NormalizeObject.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::RegexEngine;

ADT::Runtime::Object RegexEngine::MatchesPartly(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &regex_ref = Support::Runtime::GetRegexObj(args[0]);
    auto str_obj = Support::Runtime::NormalizeObject(args[1], trace);
    auto &regex = regex_ref.GetPattern();
    auto view = Support::Runtime::AccessString(str_obj);
    auto std_view = std::string_view(view.Ptr(), view.Size());

    return {
        ADT::Runtime::ObjectType::Boolean,
        RE2::PartialMatch(std_view, *regex)
    };
}
