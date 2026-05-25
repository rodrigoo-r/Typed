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
// Created by Rodrigo on 5/25/26.
//

#include "Add.h"

#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Runtime::Dictionaries
{
    ADT::Runtime::Object Add(
        ADT::List::Object &args,
        ADT::Lang::AST *trace
    )
    {
        auto &dict = Support::Runtime::GetDictionaryObj(args[0]);
        auto &key = args[1];
        auto &val = args[2];

        dict->emplace(key, val);
        return {};
    }
}