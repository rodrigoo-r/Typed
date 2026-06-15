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
// Created by Rodrigo on 6/15/26.
//

#include "Unescape.h"

#include "ADT/Lang/AST.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Strconv;

int HexDigit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return -1;
}

void AddEscapeIdx(
    ADT::Stream::File *file,
    Celery::Str::String &result
)
{
    if (file != nullptr)
    {
        file->AddEscapeIdx(result.Size());
    }
}

Celery::Str::String Strconv::Unescape(
    auto &str,
    ADT::Lang::AST *trace,
    ADT::Stream::File *file
)
{
    auto size = str.Size();

    if (memchr(str.Ptr(), '\\', size) == nullptr)
    {
        if constexpr (std::is_same_v<std::decay_t<decltype(str)>, Celery::Str::String>)
        {
            return std::move(str);
        }
        else
        {
            return {str.Ptr(), size};
        }
    }

    Celery::Str::String result;
    result.Resize(size);

    const char *ptr = str.Ptr();
    const char *end = ptr + size;

    while (ptr < end)
    {
        auto slash = static_cast<const char *>(memchr(ptr, '\\', static_cast<size_t>(end - ptr)));

        if (slash == nullptr)
        {
            result.Write(ptr, static_cast<size_t>(end - ptr));

            break;
        }

        // Copy plain text block.
        result.Write(ptr, static_cast<size_t>(slash - ptr));

        ptr = slash;

        if (ptr + 1 >= end)
        {
            if (trace != nullptr)
            {
                throw ADT::Exception::TracedUnknownFormat(trace->line, trace->column);
            }

            throw ADT::Exception::UnknownFormat();
        }

        char next = ptr[1];

        // \xHH
        if (ptr + 3 < end && (next == 'x' || next == 'X'))
        {
            int hi = HexDigit(ptr[2]);
            int lo = HexDigit(ptr[3]);

            if (hi < 0 || lo < 0)
            {
                if (trace != nullptr)
                {
                    throw ADT::Exception::TracedUnknownFormat(trace->line, trace->column);
                }

                throw ADT::Exception::UnknownFormat();
            }

            result.PushBack(static_cast<char>((hi << 4) | lo));

            ptr += 4;
            continue;
        }

        AddEscapeIdx(file, result);

        switch (next)
        {
            case '`':
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
                if (trace != nullptr)
                {
                    throw ADT::Exception::TracedUnknownFormat(trace->line, trace->column);
                }

                throw ADT::Exception::UnknownFormat();
        }

        ptr += 2;
    }

    return result;
}

template
Celery::Str::String
Strconv::Unescape<Celery::Str::String>(
    Celery::Str::String&,
    ADT::Lang::AST*,
    ADT::Stream::File*
);

template
Celery::Str::String
Strconv::Unescape<Celery::Str::External>(
    Celery::Str::External&,
    ADT::Lang::AST*,
    ADT::Stream::File*
);