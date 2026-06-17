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
#include "ReplaceAll.h"

#include "FindIndex.h"
#include "ReplaceMany.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::ReplaceAll(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto str = Support::Runtime::AccessString(args[0]);
    args.emplace_back(
        ADT::Runtime::ObjectType::Integer,
        (int)str.size()
    );

    return ReplaceMany(args, trace);
}