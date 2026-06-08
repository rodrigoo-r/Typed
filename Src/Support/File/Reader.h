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
#include <Celery/String/External.h>
#include <Celery/File/Read.h>

#include <fstream>

#include "ADT/Stream/File.h"
#include "Support/Strconv/Unescape.h"

namespace Typed::Support::File
{
    class Reader
    {
        Celery::Str::External path;

    public:
        Reader &SetPath(const Celery::Str::External &path)
        {
            this->path = path;
            return *this;
        }

        [[nodiscard]] ADT::Stream::File Read() const
        {
            auto file = Celery::File::Read(path);
            auto unescaped = Strconv::Unescape(file, nullptr);

            // Convert to a stream
            ADT::Stream::File result;
            result.Resize(unescaped.Size());

            // Write the file contents to the stream
            for (size_t i = 0; i < unescaped.Size(); ++i)
            {
                result.PushBack(unescaped[i]);
            }

            return result;
        }
    };
}