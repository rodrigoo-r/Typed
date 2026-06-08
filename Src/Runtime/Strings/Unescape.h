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
// Created by Rodrigo on 6/1/26.
//

#pragma once
#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Runtime::Strings
{
    ADT::Runtime::Object Unescape(ADT::List::Object &, ADT::Lang::AST *);
    ADT::Runtime::Object Unescape(ADT::Runtime::Object &, ADT::Lang::AST *);
}
