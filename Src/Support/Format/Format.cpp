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

ADT::Runtime::Object GetArg(
    ADT::List::Object &args,
    size_t &idx,
    ADT::Lang::AST *trace
)
{
    // Make sure there are enough arguments
    if (args.size() <= idx)
    {
        throw ADT::Exception::MismatchedArgCount(
            trace->line,
            trace->column
        );
    }

    auto &obj = args[idx];
    idx++;
    return obj;
}

template <typename Adapter>
void Format::Format(
    std::string_view &fmt,
    ADT::List::Object &args,
    Adapter &adapter,
    ADT::Lang::AST *trace
)
{
    size_t pos = 1;

    // Print the string character by character
    for (auto i = 0; i < fmt.size(); i++)
    {
        auto c = fmt[i];

        // Match formats
        if (c == '$' && fmt.size() > i + 1)
        {
            auto f = fmt[i + 1];
            auto can_continue = true;

            switch (f)
            {
                case 'S':
                {
                    auto arg = GetArg(args, pos, trace);
                    Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::String,
                        arg.type,
                        trace->line,
                        trace->column
                    );

                    can_continue = false;
                    String(arg, adapter);
                    break;
                }

                case 'F':
                {
                    auto arg = GetArg(args, pos, trace);
                    Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Float,
                        arg.type,
                        trace->line,
                        trace->column
                    );

                    can_continue = false;
                    Float(arg, adapter);
                    break;
                }

                case 'I':
                {
                    auto arg = GetArg(args, pos, trace);
                    Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Integer,
                        arg.type,
                        trace->line,
                        trace->column
                    );

                    can_continue = false;
                    Integer(arg, adapter);
                    break;
                }

                case 'B':
                {
                    auto arg = GetArg(args, pos, trace);
                    Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Boolean,
                        arg.type,
                        trace->line,
                        trace->column
                    );

                    can_continue = false;
                    Boolean(arg, adapter);
                    break;
                }

                case 'L':
                {
                    auto arg = GetArg(args, pos, trace);
                    Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::List,
                        arg.type,
                        trace->line,
                        trace->column
                    );

                    can_continue = false;
                    List(arg, adapter);
                    break;
                }

                case 'D':
                {
                    auto arg = GetArg(args, pos, trace);
                    Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Dictionary,
                        arg.type,
                        trace->line,
                        trace->column
                    );

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

        adapter.append(1, c);
    }
}

// Initialize template specialization
template
void Format::Format(
    std::string_view &fmt,
    ADT::List::Object &args,
    std::string &adapter,
    ADT::Lang::AST *trace
);

template
void Format::Format(
    std::string_view &fmt,
    ADT::List::Object &args,
    ADT::Stdout::Wrapper &adapter,
    ADT::Lang::AST *trace
);