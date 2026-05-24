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
#include "Size.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Lists;

ADT::Runtime::Object Lists::Size(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &list = Support::Runtime::GetListObj(args[0]);

    return {
        ADT::Runtime::ObjectType::Integer,
        (int)list->Size()
    };
}