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

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::RegexEngine;

ADT::Runtime::Object RegexEngine::MatchesPartly(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &regex_ref = Support::Runtime::GetRegexObj(args[0]);
    auto &regex = regex_ref.GetPattern();
    auto view = Support::Runtime::AccessString(args[1]);

    return {
        ADT::Runtime::ObjectType::Boolean,
        RE2::PartialMatch(view, *regex)
    };
}
