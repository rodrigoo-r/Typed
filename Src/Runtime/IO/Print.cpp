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
    auto &fmt_obj = args[0];
    auto &fmt = std::get<Celery::Str::External>(fmt_obj.value);
    auto line = trace->line;
    auto col = trace->column;
    Celery::Trait::VeryLarge pos = 1;

    // Print the string character by character
    for (auto i = 0; i < fmt.Size(); i++)
    {
        auto c = fmt[i];

        // Match formats
        if (c == '$' && fmt.Size() < i + 1)
        {
            auto f = fmt[i + 1];
            auto can_continue = true;

            switch (f)
            {
                case 'S':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    can_continue = false;
                    break;
                }
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
