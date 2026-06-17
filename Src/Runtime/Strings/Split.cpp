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

#include "ADT/List/Object.h"
#include "Split.h"

#include "Support/Runtime/AccessString.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Strings;

ADT::Runtime::Object Strings::Split(
    ADT::List::Object &args,
    ADT::Lang::AST *_
)
{
    auto &obj = args[0];
    auto str = Support::Runtime::AccessString(obj);
    auto delimiter = Support::Runtime::AccessString(args[1]);

    auto result = ADT::List::DynamicObject::Make();
    std::string current;
    size_t i = 0;

    while (i < str.size())
    {
        bool match = true;

        if (i + delimiter.size() <= str.size())
        {
            for (auto j = 0; j < delimiter.size(); ++j)
            {
                if (str[i + j] != delimiter[j])
                {
                    match = false;
                    break;
                }
            }
        }
        else
        {
            match = false;
        }

        if (match)
        {
            result->emplace_back(
                ADT::Runtime::ObjectType::String,
                std::move(current)
            );

            i += delimiter.size();
        }
        else
        {
            current.push_back(str[i]);
            ++i;
        }
    }

    result->emplace_back(
        ADT::Runtime::ObjectType::String,
        std::move(current)
    );

    return {
        ADT::Runtime::ObjectType::List,
        std::move(result)
    };
}