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
// Created by Rodrigo on 5/18/26.
//

#pragma once
#include <Celery/Io/Io.h>
#include <magic_enum/magic_enum.hpp>

#include "ADT/Lang/AST.h"

namespace Typed::Support::Printer
{
    class ASTPrinter
    {
        ADT::Lang::AST *root;

        void DoPrint(ADT::Lang::AST *node, int indent = 0)
        {
            auto raw_view = magic_enum::enum_name(node->type);
            Celery::Str::External view{raw_view.data(), raw_view.size()};

            for (int i = 0; i < indent; i++)
                Celery::Io::Print("  ");

            Celery::Io::Println(
                view,
                node->value.Empty() ? "" : " : ",
                node->value
            );

            for (auto &child : node->children)
            {
                DoPrint(child, indent + 1);
            }
        }

    public:
        ASTPrinter(ADT::Lang::AST *root) :
            root(root)
        {}

        void Print()
        {
            DoPrint(root);
        }
    };
}