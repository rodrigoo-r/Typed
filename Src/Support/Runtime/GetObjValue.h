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
#include <Celery/String/String.h>

#include "ADT/List/Object.h"
#include "ADT/Map/Dense.h"
#include "Support/Hash/Object.h"

namespace Typed::Support::Equality
{
    struct Object;
}

namespace Typed::ADT::Map
{
    using Object =
        Dense<
            Runtime::Object,
            Runtime::Object,
            Support::Equality::Object,
            Support::Hash::AgnosticObject<Runtime::Object>
        >;
}

namespace Typed::Support::Runtime
{
    // NOTE: We don't import Runtime::Object to avoid
    // circular dependencies

    template <typename T>
    T &GetObjValue(auto &&obj)
    {
        return std::get<T>(obj.value);
    }

    auto &GetStrObj(auto &&obj)
    {
        return GetObjValue<Celery::Str::External>(obj);
    }

    auto &GetOwnedStrObj(auto &&obj)
    {
        return GetObjValue<Celery::Str::String>(obj);
    }

    auto &GetFloatObj(auto &&obj)
    {
        return GetObjValue<float>(obj);
    }

    auto &GetIntObj(auto &&obj)
    {
        return GetObjValue<int>(obj);
    }

    auto &GetBoolObj(auto &&obj)
    {
        return GetObjValue<bool>(obj);
    }

    auto &GetListObj(auto &&obj)
    {
        return GetObjValue<ADT::List::DynamicObject>(obj);
    }

    auto &GetDictionaryObj(auto &&obj)
    {
        return GetObjValue<ADT::Map::Object>(obj);
    }
}