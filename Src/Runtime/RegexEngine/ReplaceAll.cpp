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

#include "ReplaceAll.h"

#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"
#include "Support/Runtime/GetObjValue.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::RegexEngine;

ADT::Runtime::Object RegexEngine::ReplaceAll(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &regex_ref = Support::Runtime::GetRegexObj(args[0]);
    auto source = Support::Runtime::AccessString(args[1]);
    auto target = Support::Runtime::AccessString(args[2]);
    auto &regex = regex_ref.GetPattern();

    auto std_string = std::string(source.Ptr(), source.Size());
    auto std_view = std::string_view(target.Ptr(), target.Size());

    RE2::GlobalReplace(&std_string, *regex, std_view);

    return {
        ADT::Runtime::ObjectType::OwnedString,
        Celery::Str::String(std_string.data(), std_string.size())
    };
}
