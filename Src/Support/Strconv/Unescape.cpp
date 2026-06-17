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

#include "ADT/Exception/UnknownFormat.h"
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
    std::string &result
)
{
    if (file != nullptr)
    {
        file->AddEscapeIdx(result.size());
    }
}

std::string Strconv::Unescape(
    auto &str,
    ADT::Lang::AST *trace,
    ADT::Stream::File *file
)
{
    auto size = str.size();

    if (memchr(str.data(), '\\', size) == nullptr)
    {
        if constexpr (std::is_same_v<std::decay_t<decltype(str)>, std::string>)
        {
            return std::move(str);
        }
        else
        {
            return {str.data(), size};
        }
    }

    std::string result;
    result.reserve(size);

    const char *ptr = str.data();
    const char *end = ptr + size;

    while (ptr < end)
    {
        auto slash = static_cast<const char *>(memchr(ptr, '\\', static_cast<size_t>(end - ptr)));

        if (slash == nullptr)
        {
            result.append(ptr, static_cast<size_t>(end - ptr));

            break;
        }

        // Copy plain text block.
        result.append(ptr, static_cast<size_t>(slash - ptr));

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

            result.push_back(static_cast<char>((hi << 4) | lo));

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
                result.push_back(next);
                break;

            case 'a':
                result.push_back('\a');
                break;

            case 'b':
                result.push_back('\b');
                break;

            case 'f':
                result.push_back('\f');
                break;

            case 'n':
                result.push_back('\n');
                break;

            case 'r':
                result.push_back('\r');
                break;

            case 't':
                result.push_back('\t');
                break;

            case 'v':
                result.push_back('\v');
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
std::string
Strconv::Unescape<std::string>(
    std::string&,
    ADT::Lang::AST*,
    ADT::Stream::File*
);

template
std::string
Strconv::Unescape<std::string_view>(
    std::string_view&,
    ADT::Lang::AST*,
    ADT::Stream::File*
);