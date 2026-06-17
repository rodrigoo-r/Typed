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
#include "FindIndex.h"

#include "FindIndexes.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::FindIndex(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    args.emplace_back(
        ADT::Runtime::ObjectType::Integer,
        1
    );

    auto obj = FindIndexes(args, _);
    auto &indexes = Support::Runtime::GetListObj(obj);

    if (indexes->empty()) return {
        ADT::Runtime::ObjectType::Integer,
        -1
    };

    return indexes->front();
}