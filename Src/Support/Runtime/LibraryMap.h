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
// Created by Rodrigo on 5/20/26.
//

#pragma once
#include <Celery/Misc/Hash.h>
#include <Celery/String/External.h>


#include "ADT/Map/Dense.h"
#include "Runtime/Dictionaries/Package.h"
#include "Runtime/FileSystem/Package.h"
#include "Runtime/IO/Package.h"
#include "Runtime/Lists/Package.h"
#include "Runtime/Math/Package.h"
#include "Runtime/RegexEngine/Package.h"
#include "Runtime/Strings/Package.h"

namespace Typed::Support::Runtime
{
    inline ADT::Map::Dense<
        Celery::Str::External,
        ADT::Map::Procedure,
        Celery::Misc::Hash
    > LibraryMap = {
        {"IO", Typed::Runtime::IO::Package},
        {"Lists", Typed::Runtime::Lists::Package},
        {"Dictionaries", Typed::Runtime::Dictionaries::Package},
        {"Strings", Typed::Runtime::Strings::Package},
        {"Math", Typed::Runtime::Math::Package},
        {"File_System", Typed::Runtime::FileSystem::Package},
        {"Regex_Engine", Typed::Runtime::RegexEngine::Package}
    };
}