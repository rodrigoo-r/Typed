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

#include "ADT/Exception/UnknownProcedure.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

ADT::Runtime::Object Walker::Call(
    VariableStack &stack,
    TreePtr body
)
{
    auto &children = body->children;
    auto &name = children[0]->value;
    auto line = body->line;
    auto column = body->column;
    auto proc = runnable.procedures.find(name);

    if (proc == runnable.procedures.end())
    {
        throw ADT::Exception::UnknownProcedure(line, column);
    }

    if (children.size() == 1)
    {
        ADT::List::Object args;
        return Procedure(proc->second, args, body);
    }

    // Get args too
    ADT::List::Object args;
    auto args_node = children[1];

    for (auto &arg_node : args_node->children)
    {
        auto arg = arg_node->children[0];
        args.push_back(Expression(stack, arg));
    }

    return Procedure(proc->second, args, body);
}
