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
// Created by Rodrigo on 6/8/26.
//

#pragma once
#include <Celery/String/String.h>

#include "ADT/Exception/UnknownFormat.h"
#include "ADT/Stream/File.h"
#include "ADT/Lang/AST.h"

namespace Typed::Support::Strconv
{
    Celery::Str::String Unescape(
        auto &str,
        ADT::Lang::AST *trace,
        ADT::Stream::File *file
    );
}