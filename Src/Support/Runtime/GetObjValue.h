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

#pragma once
#include <Celery/String/External.h>

#include "ADT/Runtime/Object.h"

namespace Typed::Support::Runtime
{
    template <typename T>
    T &GetObjValue(ADT::Runtime::Object &obj)
    {
        return std::get<T>(obj.value);
    }

    inline Celery::Str::External &GetStrObj(ADT::Runtime::Object &obj)
    {
        return GetObjValue<Celery::Str::External>(obj);
    }

    inline Celery::Str::String &GetOwnedStrObj(ADT::Runtime::Object &obj)
    {
        return GetObjValue<Celery::Str::String>(obj);
    }

    inline float &GetFloatObj(ADT::Runtime::Object &obj)
    {
        return GetObjValue<float>(obj);
    }

    inline int &GetIntObj(ADT::Runtime::Object &obj)
    {
        return GetObjValue<int>(obj);
    }

    inline bool &GetBoolObj(ADT::Runtime::Object &obj)
    {
        return GetObjValue<bool>(obj);
    }
}