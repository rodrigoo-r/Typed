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
// Created by Rodrigo on 5/30/26.
//

#include "ADT/List/Object.h"

#include "HyperbolicTangentDegrees.h"

#include <complex>

#include "Support/Math/CalculateDegrees.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::Math;

ADT::Runtime::Object Math::HyperbolicTangentDegrees(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    return Support::Math::CalculateDegrees(args, trace, std::tanhf);
}