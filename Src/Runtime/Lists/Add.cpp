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

#include "ADT/Lang/AST.h"
#include "ADT/List/Object.h"
#include "Add.h"

#include "ADT/Exception/MismatchedType.h"
#include "Support/Printer/ASTPrinter.h"
#include "Support/Runtime/NormalizeObject.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Lists;

ADT::Runtime::Object Lists::Add(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &list = Support::Runtime::GetListObj(args[0]);

    // Push all args to the list
    for (auto i = 1; i < args.Size(); i++)
    {
        auto &arg = args[i];

        // Make sure the object isn't void
        if (
            arg.type == ADT::Runtime::ObjectType::Void ||
            arg.type == ADT::Runtime::ObjectType::Any
        )
        {
            throw ADT::Exception::MismatchedType(
                trace->line,
                trace->column
            );
        }

        list->PushBack(Support::Runtime::NormalizeObject(arg, trace));
    }

    return {};
}