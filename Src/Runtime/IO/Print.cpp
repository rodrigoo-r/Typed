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

#include "Print.h"

#include "ADT/Exception/MismatchedArgCount.h"
#include "Support/Printer/ASTPrinter.h"
#include "Support/Runtime/GetObjValue.h"
#include "Support/Runtime/TypeChecker.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::IO;

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

void IO::Print(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &fmt = Support::Runtime::GetStrObj(args[0]);
    auto line = trace->line;
    auto col = trace->column;
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
                    Support::Runtime::TypeCheck(
                        arg.type,
                        ADT::Runtime::ObjectType::String,
                        line,
                        col
                    );

                    auto &val = Support::Runtime::GetStrObj(arg);
                    can_continue = false;
                    Celery::Io::Print(val);

                    break;
                }

                default: break;
            }

            // Skip the next character if we found a format
            if (!can_continue)
            {
                i++;
                continue;
            }
        }

        Celery::Io::Print(c);
    }
}
