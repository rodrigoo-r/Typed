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

#include <Celery/Array/Stream.h>

#include "Support/Runtime/GetObjValue.h"

namespace Typed::ADT::Stream
{
    using EscapeSet =
        ankerl::unordered_dense::set<size_t>;

    class File :
        public Celery::Array::Stream<char>
    {
    protected:
        friend class FileBase;

        EscapeSet escape_idx;

    public:
        void AddEscapeIdx(size_t idx)
        {
            escape_idx.insert(idx);
        }

        bool IsEscape(size_t idx)
        {
            return escape_idx.contains(idx);
        }

        void ClearEscapeIdx()
        {
            ankerl::unordered_dense::set<size_t> other;

            escape_idx.clear();
            escape_idx.swap(other);
        }
    };

    using FileView =
        Celery::Array::External<char>;
}