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
// Created by Rodrigo on 6/15/26.
//

#pragma once
#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Runtime::FileSystem
{
    ADT::Runtime::Object ScanDirectory(
        ADT::List::Object &args,
        ADT::Lang::AST *trace
    );
}