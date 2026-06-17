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

#include "ADT/Lang/AST.h"
#include "ADT/List/Object.h"
#include "Join.h"

#include "ADT/Exception/MismatchedType.h"
#include "Support/Format/Boolean.h"
#include "Support/Format/Dictionary.h"
#include "Support/Format/Float.h"
#include "Support/Format/Integer.h"
#include "Support/Format/List.h"
#include "Support/Format/String.h"
#include "Support/Printer/ASTPrinter.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Lists;

ADT::Runtime::Object Lists::Join(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &list = Support::Runtime::GetListObj(args[0]);
    auto delim = Support::Runtime::AccessString(args[1]);
    Celery::Str::String result;

    // Transverse the list
    for (auto &item : *list)
    {
        switch (item.type)
        {
            case ADT::Runtime::ObjectType::String:
            {
                Support::Format::String(item, result);
                break;
            }

            case ADT::Runtime::ObjectType::Integer:
            {
                Support::Format::Integer(item, result);
                break;
            }

            case ADT::Runtime::ObjectType::Float:
            {
                Support::Format::Float(item, result);
                break;
            }

            case ADT::Runtime::ObjectType::Boolean:
            {
                Support::Format::Boolean(item, result);
                break;
            }

            case ADT::Runtime::ObjectType::List:
            {
                Support::Format::List(item, result);
                break;
            }

            case ADT::Runtime::ObjectType::Dictionary:
            {
                Support::Format::Dictionary(item, result);
                break;
            }

            default:
            {
                result.Write("[Non_Formattable]", 17);
                break;
            }
        }
    }

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}