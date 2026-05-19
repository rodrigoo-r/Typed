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

#include "ADT/Stream/External.h"
#include "Parser.h"
#include "Support/Equality/TokenType.h"
#include "Support/Stream/Extract.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

struct ExpressionQueueElement
{
    Machine::TokenStreamView tokens;
    Machine::TreePtr parent;
};

using Queue =
    Celery::Array::Vector<ExpressionQueueElement>;

void Machine::Expression(TreePtr parent)
{
    auto expr = Support::Stream::Extract<
        ADT::Lang::Token,
        Support::Equality::TokenType
    >(
        tokens,
        ADT::Lang::TokenType::Semicolon
    );

    Expression(parent, expr);
}

void Machine::Expression(TreePtr body, const TokenStreamView& input)
{
    Queue queue;
    queue.EmplaceBack(input, body);

    while (!queue.Empty())
    {
        auto [expr, parent] = queue.Back();
        queue.PopBack();

        // Create the expression AST
        auto ast = AllocateBase(expr.Peek(), ADT::Lang::ASTType::Expression);
        parent->children.PushBack(ast);

        // Get the candidate to determine the expression type

    }
}