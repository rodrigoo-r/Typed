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

#pragma once

#include "ADT/Lang/AST.h"
#include "ADT/List/Object.h"

namespace Typed::Runtime::RegexEngine
{
    ADT::Runtime::Object ReplaceOne(
        ADT::List::Object &,
        ADT::Lang::AST *
    );
}