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

namespace Typed::Support::File
{
    class Reader
    {
        Celery::Str::External Path;

    public:
        Reader &SetPath(const Celery::Str::External &path)
        {
            Path = path;
            return *this;
        }

        [[nodiscard]] ADT::Stream::File Read() const
        {
            auto file = Celery::File::Read(Path);

            // Convert to a stream
            ADT::Stream::File result;
            result.Resize(file.Size());

            // Write the file contents to the stream
            for (size_t i = 0; i < file.Size(); ++i)
            {
                result.PushBack(file[i]);
            }

            return result;
        }
    };
}