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

#include "ExtractMatches.h"

#include "ADT/Runtime/Object.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/ConvertToString.h"
#include "Support/Runtime/GetObjValue.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::RegexEngine;

ADT::Runtime::Object RegexEngine::ExtractMatches(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &regex_ref = Support::Runtime::GetRegexObj(args[0]);
    auto source = Support::Runtime::AccessString(args[1]);
    auto &regex = regex_ref.GetPattern();

    auto std_view = std::string_view(source.Ptr(), source.Size());
    std::string match;
    auto result = ADT::List::DynamicObject::Make();

    while (RE2::FindAndConsume(&std_view, *regex, &match))
    {
        result->EmplaceBack(
            ADT::Runtime::ObjectType::OwnedString,
            Celery::Str::String{match.data(), match.size()}
        );
    }

    return {
        ADT::Runtime::ObjectType::List,
        std::move(result)
    };
}
