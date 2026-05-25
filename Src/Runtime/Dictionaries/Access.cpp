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

#include "Access.h"

#include "ADT/Exception/UnknownElement.h"
#include "ADT/Lang/AST.h"
#include "ADT/Runtime/Object.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Dictionaries;

ADT::Runtime::Object Dictionaries::Access(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &dict = Support::Runtime::GetDictionaryObj(args[0]);
    auto &key = args[1];

    auto it = dict->find(key);
    if (it == dict->end())
    {
        throw ADT::Exception::UnknownElement(
            trace->line,
            trace->column
        );
    }

    return it->second;
}