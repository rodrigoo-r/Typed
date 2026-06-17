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
// Created by Rodrigo on 5/21/26.
//

#include "ADT/Exception/ExpectedInitialValue.h"
#include "ADT/Exception/UnexpectedToken.h"
#include "Support/Runtime/AccessString.h"
#include "Support/Runtime/TypeChecker.h"
#include "Walker.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Backend;

void Walker::Declare(
    VariableStack &stack,
    TreePtr body
)
{
    // Note: redefining variables is allowed in Typed
    auto &name = body->children[0]->value;
    auto &type = body->children[1]->type;
    bool has_init = body->children.size() > 2;

    if (
        type != ADT::Lang::ASTType::List &&
        type != ADT::Lang::ASTType::Dictionary &&
        !has_init
    )
    {
        throw ADT::Exception::ExpectedInitialValue(
            body->line,
            body->column
        );
    }

    if (type == ADT::Lang::ASTType::List && !has_init)
    {
        ADT::Runtime::Object obj;
        obj.type = ADT::Runtime::ObjectType::List;
        obj.value = ADT::List::DynamicObject::Make();
        stack.Emplace(name, std::move(obj));
    } else if (type == ADT::Lang::ASTType::Dictionary && !has_init)
    {
        ADT::Runtime::Object obj;
        obj.type = ADT::Runtime::ObjectType::Dictionary;
        obj.value = ADT::Map::Object::Make();
        stack.Emplace(name, std::move(obj));
    }
    else if (type == ADT::Lang::ASTType::Regex)
    {
        auto &value = body->children[2];
        auto obj = Expression(stack, value);

        // Best case: if the object is already a regex
        if (obj.type == ADT::Runtime::ObjectType::Regex)
        {
            stack.Emplace(name, std::move(obj));
            return;
        }

        Support::Runtime::TypeCheck(
            ADT::Runtime::ObjectType::String,
            obj.type,
            body->line,
            body->column
        );

        ADT::Regex::Ref regex;
        auto str = Support::Runtime::AccessString(obj);

        regex.Build(str);
        stack.Emplace(
            name,
            ADT::Runtime::ObjectType::Regex,
            std::move(regex)
        );
    }
    else
    {
        auto &value = body->children[2];
        auto obj = Expression(stack, value);

        // Do type checking
        Support::Runtime::TypeCheck(
            type == ADT::Lang::ASTType::String ?
                ADT::Runtime::ObjectType::String :
            type == ADT::Lang::ASTType::Integer ?
                ADT::Runtime::ObjectType::Integer :
            type == ADT::Lang::ASTType::Float ?
                ADT::Runtime::ObjectType::Float :
            type == ADT::Lang::ASTType::Boolean ?
                ADT::Runtime::ObjectType::Boolean :
            type == ADT::Lang::ASTType::List ?
                ADT::Runtime::ObjectType::List :
                ADT::Runtime::ObjectType::Dictionary,
            obj.type,
            body->line,
            body->column
        );

        stack.Emplace(name, std::move(obj));
    }
}