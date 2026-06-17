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

#include "Integer.h"

#include "ADT/Runtime/Object.h"
#include "ADT/Stdout/Wrapper.h"

using namespace Typed;
using namespace Typed::Support;
using namespace Typed::Support::Format;

template<typename Adapter>
void Format::Integer(
    ADT::Runtime::Object &obj,
    Adapter &adapter
)
{
    auto &value = Runtime::GetIntObj(obj);

    using ValueType = int;
    using UValue = std::make_unsigned_t<ValueType>;
    using AbsValueType = std::conditional_t<
        std::is_unsigned_v<ValueType>,
        ValueType,
        UValue
    >;

    // Handle zero explicitly
    if (value == 0)
    {
        adapter.append("0", 1);
        return;
    }

    // Handle negative values for signed types
    bool negative = false;
    if constexpr (!std::is_unsigned_v<ValueType>)
    {
        // Check only if the value type is signed
        if (value < 0)
        {
            negative = true; // Mark as negative
            adapter.append("-", 1);
        }
    }

    // Work with absolute value for digit extraction
    AbsValueType abs_value = value;

    // Change only for signed types
    if constexpr (std::is_signed_v<ValueType>)
    {
        if (negative)
        {
            // Handle potential overflow when negating
            abs_value = static_cast<UValue>(-(value + 1)) + 1;
        }
    }

    // Find the highest power of 10 less than or equal to value
    AbsValueType div = 1;
    while (abs_value / div >= 10)
        div *= 10;

    // Write digits from most to least significant
    while (div > 0)
    {
        const int digit = static_cast<int>(abs_value / div);
        adapter.append(1, static_cast<char>('0' + digit));
        abs_value %= div;
        div /= 10;
    }
}

template
void Format::Integer(
    ADT::Runtime::Object &,
    ADT::Stdout::Wrapper &
);

template
void Format::Integer(
    ADT::Runtime::Object &,
    std::string &
);
