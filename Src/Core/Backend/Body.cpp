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

#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

ADT::Runtime::Object Walker::Body(
    ProcedureRef procedure,
    TreePtr body,
    VariableStack &stack,
    bool create_scope
)
{
    if (create_scope)
        stack.PushScope();

    // Begin execution
    for (auto ast : body->children)
    {
        switch (ast->type)
        {
            case ADT::Lang::ASTType::Expression:
            {
                Expression(stack, ast);
                break;
            }

            case ADT::Lang::ASTType::Declare:
            {
                Declare(stack, ast);
                break;
            }

            case ADT::Lang::ASTType::Return:
            {
                return Return(procedure, stack, ast);
            }

            case ADT::Lang::ASTType::If:
            {
                If(procedure, stack, ast);
                break;
            }

            case ADT::Lang::ASTType::ConditionGroup:
            {
                ConditionGroup(procedure, stack, ast);
                break;
            }

            case ADT::Lang::ASTType::For:
            {
                For(procedure, stack, ast);
                break;
            }

            default: break;
        }
    }

    if (create_scope)
        stack.PopScope();

    // Return an empty object otherwise
    return {};
}
