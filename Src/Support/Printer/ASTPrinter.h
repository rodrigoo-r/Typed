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
#include <magic_enum/magic_enum.hpp>

#include "ADT/Lang/AST.h"

namespace Typed::Support::Printer
{
    class ASTPrinter
    {
        ADT::Lang::AST *root;

        void DoPrint(ADT::Lang::AST *node, int indent = 0)
        {
            auto view = magic_enum::enum_name(node->type);

            for (int i = 0; i < indent; i++)
                std::cout << "  ";

            std::cout
                << view
                << (node->value.empty() ? "" : " : ")
                << node->value
            ;

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