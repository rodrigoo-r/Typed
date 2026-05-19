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
// Created by Rodrigo on 5/19/26.
//

#include "PreWalker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::MiddleEnd;

void PreWalker::Procedure(TreePtr ast)
{
    // Get the procedure's name
    auto &name = ast->value;
    ADT::PreWalker::Procedure proc;

    // Process arguments, if any
    auto body = ast->children[0];
    if (body->type == ADT::Lang::ASTType::Arguments)
    {
        for (auto arg : body->children)
        {
            auto &arg_name = arg->children[0]->value;
            auto arg_type = arg->children[1]->type;
            ADT::Runtime::ObjectType runtime_type = ADT::Runtime::ObjectType::Integer;

            switch (arg_type)
            {
                case ADT::Lang::ASTType::Integer:
                {
                    runtime_type = ADT::Runtime::ObjectType::Integer;
                    break;
                }

                case ADT::Lang::ASTType::Boolean:
                {
                    runtime_type = ADT::Runtime::ObjectType::Boolean;
                    break;
                }

                case ADT::Lang::ASTType::String:
                {
                    runtime_type = ADT::Runtime::ObjectType::String;
                    break;
                }

                case ADT::Lang::ASTType::Float:
                {
                    runtime_type = ADT::Runtime::ObjectType::Float;
                    break;
                }

                default: break;
            }

            // Push the argument
            proc.arguments.emplace(
                arg_name,
                runtime_type
            );
        }

        body = ast->children[1];
    }

    // Set the body
    proc.body = body;

    // Push the procedure to the map
    result.procedures.emplace(
        name,
        std::move(proc)
    );
}
