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
#include "Support/Runtime/NormalizeObject.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::ReplaceAll(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto str_normal = Support::Runtime::NormalizeObject(args[0], trace);
    auto str = Support::Runtime::AccessString(str_normal);
    args.EmplaceBack(
        ADT::Runtime::ObjectType::Integer,
        (int)str.Size()
    );

    return ReplaceMany(args, trace);
}