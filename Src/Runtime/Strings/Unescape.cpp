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
// Created by Rodrigo on 6/1/26.
//

#include "ADT/List/Object.h"
#include "Unescape.h"

#include <charconv>

#include "ADT/Exception/UnknownFormat.h"
#include "ADT/Lang/AST.h"
#include "ADT/Stream/External.h"
#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Unescape(
    ADT::Runtime::Object &obj,
    ADT::Lang::AST *trace
)
{
    auto str = Support::Runtime::AccessString(obj);
    auto size = str.Size();

    if (memchr(str.Ptr(), '\\', size) == nullptr)
    {
        return obj;
    }

    Celery::Str::String result;

    // Write the string
    for (auto i = 0; i < size;) {
        auto c = str[i];

        if (
            i + 3 < size &&
            c == '\\' &&
            std::tolower(str[i + 1]) == 'x'
        )
        {
            std::string_view hex(str.Ptr() + i + 2, 2);
            int val;
            auto [_, ec] = std::from_chars(hex.data(), hex.data() + hex.size(), val);

            if (ec == std::errc{})
            {
                throw ADT::Exception::UnknownFormat(
                    trace->line,
                    trace->column
                );
            }

            result.PushBack(static_cast<char>(val));
            i += 4;
        }
        else if (
            i + 1 < size &&
            c == '\\'
        )
        {
            auto next = str[i + 1];
            switch (next)
            {
                case '"':
                case '\'':
                case '\\':
                    result.PushBack(next);
                    break;

                case 'a':
                    result.PushBack('\a');
                    break;

                case 'b':
                    result.PushBack('\b');
                    break;

                case 'f':
                    result.PushBack('\f');
                    break;

                case 'n':
                    result.PushBack('\n');
                    break;

                case 'r':
                    result.PushBack('\r');
                    break;

                case 't':
                    result.PushBack('\t');
                    break;

                case 'v':
                    result.PushBack('\v');
                    break;

                default:
                    throw ADT::Exception::UnknownFormat(
                        trace->line,
                        trace->column
                    );
            }

            i += 2;
        }
        else
        {
            result.PushBack(c);
            ++i;
        }
    }

    return {
        ADT::Runtime::ObjectType::String,
        std::move(result)
    };
}

ADT::Runtime::Object Strings::Unescape(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    return Unescape(args[0], trace);
}