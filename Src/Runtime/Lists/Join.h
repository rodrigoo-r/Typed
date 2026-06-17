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
// Created by Rodrigo on 7/16/26.
//

#pragma once
#include "ADT/Lang/AST.h"
#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Runtime::Lists
{
    ADT::Runtime::Object Join(ADT::List::Object &, ADT::Lang::AST *);
}