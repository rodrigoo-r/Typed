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
// Created by Rodrigo on 5/24/26.
//

#include "ADT/List/Object.h"
#include "Trim.h"

#include "TrimLeft.h"
#include "TrimRight.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Trim(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto left = TrimLeft(args, _);
    args[0] = std::move(left);

    return TrimRight(args, _);
}