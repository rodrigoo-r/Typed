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
// Created by Rodrigo on 5/16/26.
//

#pragma once

#include <fstream>

#include "ADT/Exception/CouldNotOpenFile.h"
#include "ADT/Stream/File.h"
#include "Support/Strconv/Unescape.h"

namespace Typed::Support::File
{
    class Reader
    {
        std::string_view path;

    public:
        Reader &SetPath(const std::string_view &path)
        {
            this->path = path;
            return *this;
        }

        ADT::Stream::File Read()
        {
            // Convert to a stream
            ADT::Stream::File result;

            std::ifstream file_stream(path.data());
            if (!file_stream.is_open()) throw std::filesystem::filesystem_error("Could not open file", std::error_code());

            std::stringstream stream;
            stream << file_stream.rdbuf();

            auto file = stream.str();
            file_stream.close();
            auto unescaped = Strconv::Unescape(file, nullptr, &result);

            result.reserve(unescaped.size());
            result.shrink_to_fit();

            // Write the file contents to the stream
            for (char i : unescaped)
            {
                result.push_back(i);
            }

            return result;
        }
    };
}