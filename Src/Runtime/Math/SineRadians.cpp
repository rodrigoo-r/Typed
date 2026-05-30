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
// Created by Rodrigo on 5/27/26.
//

#include "ADT/List/Object.h"

#include "SineRadians.h"

#include "Support/Math/Calculate.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Math;

ADT::Runtime::Object Math::SineRadians(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    return Support::Math::Calculate(args, trace, std::sinf);
}