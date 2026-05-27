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
// Created by Rodrigo on 5/27/26.
//

#include "Format.h"

#include <Celery/Io/Stream.h>

#include "ADT/Exception/MismatchedArgCount.h"
#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"
#include "Boolean.h"
#include "Dictionary.h"
#include "Float.h"
#include "Integer.h"
#include "List.h"
#include "String.h"
#include "Support/Runtime/TypeChecker.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

ADT::Runtime::Object &GetArg(
    ADT::List::Object &args,
    Celery::Trait::VeryLarge &idx,
    Celery::Trait::VeryLarge &line,
    Celery::Trait::VeryLarge &col
)
{
    // Make sure there are enough arguments
    if (args.Size() <= idx)
    {
        throw ADT::Exception::MismatchedArgCount(line, col);
    }

    auto &obj = args[idx];
    idx++;
    return obj;
}

template <typename Adapter>
void Format::Format(
    Celery::Str::External &fmt,
    ADT::List::Object &args,
    Adapter &adapter,
    Celery::Trait::VeryLarge line,
    Celery::Trait::VeryLarge col
)
{
    Celery::Trait::VeryLarge pos = 1;

    // Print the string character by character
    for (auto i = 0; i < fmt.Size(); i++)
    {
        auto c = fmt[i];

        // Match formats
        if (c == '$' && fmt.Size() > i + 1)
        {
            auto f = fmt[i + 1];
            auto can_continue = true;

            switch (f)
            {
                case 'S':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Runtime::TypeCheck(ADT::Runtime::ObjectType::String, arg.type, line, col);

                    can_continue = false;
                    String(arg, adapter);
                    break;
                }

                case 'F':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Runtime::TypeCheck(ADT::Runtime::ObjectType::Float, arg.type, line, col);

                    can_continue = false;
                    Float(arg, adapter);
                    break;
                }

                case 'I':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Runtime::TypeCheck(ADT::Runtime::ObjectType::Integer, arg.type, line, col);

                    can_continue = false;
                    Integer(arg, adapter);
                    break;
                }

                case 'B':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Runtime::TypeCheck(ADT::Runtime::ObjectType::Boolean, arg.type, line, col);

                    can_continue = false;
                    Boolean(arg, adapter);
                    break;
                }

                case 'L':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Runtime::TypeCheck(ADT::Runtime::ObjectType::List, arg.type, line, col);

                    can_continue = false;
                    List(arg, adapter);
                    break;
                }

                case 'D':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Runtime::TypeCheck(ADT::Runtime::ObjectType::Dictionary, arg.type, line, col);

                    can_continue = false;
                    Dictionary(arg, adapter);
                    break;
                }

                default:
                    break;
            }

            // Skip the next character if we found a format
            if (!can_continue)
            {
                i++;
                continue;
            }
        }

        adapter.Write(c);
    }
}

// Initialize template specialization
template
void Format::Format(
    Celery::Str::External &fmt,
    ADT::List::Object &args,
    Celery::Str::String &adapter,
    Celery::Trait::VeryLarge line,
    Celery::Trait::VeryLarge col
);

template
void Format::Format(
    Celery::Str::External &fmt,
    ADT::List::Object &args,
    ADT::Stdout::Wrapper &adapter,
    Celery::Trait::VeryLarge line,
    Celery::Trait::VeryLarge col
);