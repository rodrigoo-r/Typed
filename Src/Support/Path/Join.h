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
// Created by Rodrigo on 5/29/26.
//

#pragma once
#include <filesystem>

#include "ADT/Lang/AST.h"
#include "ADT/List/Object.h"
#include "ADT/Runtime/Object.h"
#include "Support/Runtime/TypeChecker.h"

namespace Typed::Support::Path
{
    inline std::filesystem::path Join(
        ADT::List::Object &args,
        ADT::Lang::AST *trace
    )
    {
        auto &obj = args[0];
        auto &list = Support::Runtime::GetListObj(obj);

        if (list->Empty()) return {};

        std::filesystem::path path;

        // Build the path iteratively
        for (auto &elem : *list)
        {
            Runtime::TypeCheck(
                ADT::Runtime::ObjectType::String,
                list->Front().type,
                trace->line,
                trace->column
            );

            if (elem.type == ADT::Runtime::ObjectType::String)
            {
                auto &str = Runtime::GetStrObj(elem);
                std::string owned{str.Ptr(), str.Size()};

                path /= owned;
            } else
            {
                auto &str = Runtime::GetOwnedStrObj(elem);
                std::string owned{str.Ptr(), str.Size()};

                path /= owned;
            }
        }

        return path;
    }
}