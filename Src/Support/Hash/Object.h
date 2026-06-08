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
#include <Celery/String/String.h>
#include <Celery/Trait/Default.h>
#include <xxhash.h>

#include "ADT/Runtime/ObjectType.h"

namespace Typed::Support::Hash
{
    template <typename T>
    struct AgnosticObject
    {
        using is_avalanching = void;
        using is_transparent = void;

        Celery::Trait::VeryLarge operator()(const T &obj) const
        {
            switch (obj.type)
            {
                case ADT::Runtime::ObjectType::Integer:
                {
                    auto &int_val = std::get<int>(obj.value);
                    return XXH3_64bits(&int_val, sizeof(int));
                }

                case ADT::Runtime::ObjectType::Float:
                {
                    auto &float_val = std::get<float>(obj.value);
                    return XXH3_64bits(&float_val, sizeof(float));
                }

                case ADT::Runtime::ObjectType::String:
                {
                    if (std::holds_alternative<Celery::Str::External>(obj.value))
                    {
                        auto &str_val = std::get<Celery::Str::External>(obj.value);
                        return XXH3_64bits(str_val.Ptr(), str_val.Size());
                    }

                    auto &str_val = std::get<Celery::Str::String>(obj.value);
                    return XXH3_64bits(str_val.Ptr(), str_val.Size());
                }

                case ADT::Runtime::ObjectType::Boolean:
                {
                    auto &bool_val = std::get<bool>(obj.value);
                    return XXH3_64bits(&bool_val, sizeof(bool));
                }
                default:
                {
                    return XXH3_64bits(
                        &obj,
                        sizeof(T)
                    );
                }
            }
        }
    };
}