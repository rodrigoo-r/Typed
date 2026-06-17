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

#include "Float.h"

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"
#include "Integer.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Float(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto &value = Runtime::GetFloatObj(obj);
    using FloatType = std::remove_cv_t<std::remove_reference_t<decltype(value)>>;

    // Handle NaN and Inf
    if (std::isnan(value))
    {
        adapter.append("NaN", 3);
        return;
    }

    if (std::isinf(value))
    {
        if (value < 0) adapter.append(1, '-');
        adapter.append("INF", 3);
        return;
    }

    // Handle sign
    if (value < 0)
    {
        adapter.append(1, '-');
        value = -value;
    }

    // Extract integer part
    auto int_part = static_cast<uint64_t>(value);
    auto frac_part = value - static_cast<FloatType>(int_part);

    // Write integer part using existing Itoa logic
    ADT::Runtime::Object int_obj{
        ADT::Runtime::ObjectType::Integer,
        (int)int_part
    };

    Integer(int_obj, adapter);

    adapter.append(1, '.');

    // Write fractional digits
    for (int i = 0; i < 2; ++i)
    {
        frac_part *= 10;
        int digit = static_cast<int>(frac_part);
        adapter.append(1, static_cast<char>('0' + digit));
        frac_part -= digit;
        if (frac_part <= std::numeric_limits<FloatType>::epsilon())
            break;
    }
}

template
void Format::Float(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Float(
    ADT::Runtime::Object &,
    std::string &
);
