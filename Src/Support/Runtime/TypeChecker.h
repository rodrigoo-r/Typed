//
// Created by Rodrigo on 5/20/26.
//

#pragma once
#include "ADT/Exception/MismatchedType.h"
#include "ADT/Runtime/Object.h"

namespace Typed::Support::Runtime
{
    inline void TypeCheck(
        ADT::Runtime::ObjectType expected,
        ADT::Runtime::ObjectType actual,
        Celery::Trait::VeryLarge line,
        Celery::Trait::VeryLarge column
    )
    {
        // Find the expected type
        if (
            expected != actual &&
            expected != ADT::Runtime::ObjectType::Any
        )
        {
            throw ADT::Exception::MismatchedType(
                line,
                column
            );
        }
    }
}