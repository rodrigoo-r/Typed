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

void Machine::Expression(TreePtr body, TokenStreamView input)
{
    Queue queue;
    queue.EmplaceBack(input, body);

    while (!queue.Empty())
    {
        auto el = queue.Back();
        queue.PopBack();
    }
}