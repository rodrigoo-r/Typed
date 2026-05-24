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
// Created by Rodrigo on 5/23/26.
//

#pragma once
#include <Celery/Misc/StringEqual.h>


#include "ADT/Lang/Token.h"
#include "ADT/Runtime/Object.h"
#include "Support/Runtime/GetObjValue.h"

namespace Typed::Support::Equality
{
    struct Object
    {
        using is_transparent = void;

        static bool Equals(
            ADT::Runtime::Object &lhs,
            ADT::Runtime::Object &rhs
        )
        {
            if (
                lhs.type == ADT::Runtime::ObjectType::OwnedString
            )
            {
                // Account for special cases
                if (rhs.type == ADT::Runtime::ObjectType::OwnedString)
                {
                    auto &left_str = Runtime::GetOwnedStrObj(lhs);
                    auto &right_str = Runtime::GetOwnedStrObj(rhs);
                    return Celery::Misc::StringEquality::Cmp(left_str, right_str);
                }

                auto &left_str = Runtime::GetOwnedStrObj(lhs);
                auto &right_str = Runtime::GetStrObj(rhs);
                return Celery::Misc::StringEquality::Cmp(left_str, right_str);
            }

            if (
                lhs.type == ADT::Runtime::ObjectType::String
            )
            {
                // Account for special cases
                if (rhs.type == ADT::Runtime::ObjectType::OwnedString)
                {
                    auto &left_str = Runtime::GetStrObj(lhs);
                    auto &right_str = Runtime::GetOwnedStrObj(rhs);
                    return Celery::Misc::StringEquality::Cmp(left_str, right_str);
                }

                auto &left_str = Runtime::GetStrObj(lhs);
                auto &right_str = Runtime::GetStrObj(rhs);
                return Celery::Misc::StringEquality::Cmp(left_str, right_str);
            }

            if (lhs.type == ADT::Runtime::ObjectType::Boolean)
            {
                auto &left_bool = Runtime::GetBoolObj(lhs);
                auto &right_bool = Runtime::GetBoolObj(rhs);
                return left_bool == right_bool;
            }

            if (lhs.type == ADT::Runtime::ObjectType::Integer)
            {
                auto &left_int = Runtime::GetIntObj(lhs);
                auto &right_int = Runtime::GetIntObj(rhs);
                return left_int == right_int;
            }

            if (lhs.type == ADT::Runtime::ObjectType::Float)
            {
                auto &left_float = Runtime::GetFloatObj(lhs);
                auto &right_float = Runtime::GetFloatObj(rhs);
                return left_float == right_float;
            }

            // Lists/Dictionaries are not directly comparable
            return false;
        }

        bool operator()(
            ADT::Runtime::Object &lhs,
            ADT::Runtime::Object &rhs
        ) const noexcept
        {
            return Equals(
                lhs,
                rhs
            );
        }
    };
}