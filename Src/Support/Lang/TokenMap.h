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

#pragma once
#include <Celery/String/External.h>
#include <Celery/Misc/Hash.h>


#include "ADT/Lang/TokenType.h"
#include "ADT/Map/Dense.h"

namespace Typed::Support::Lang
{
    inline ADT::Map::Dense<
        Celery::Str::External,
        ADT::Lang::TokenType,
        Celery::Misc::Hash
    > TokenMap = {
        {"Use", ADT::Lang::TokenType::Use},

        {"Procedure", ADT::Lang::TokenType::Procedure},
        {"Begin", ADT::Lang::TokenType::Begin},
        {"End_Procedure", ADT::Lang::TokenType::EndProcedure},
        {"End_If", ADT::Lang::TokenType::EndIf},
        {"End_Call", ADT::Lang::TokenType::EndCall},

        {"as", ADT::Lang::TokenType::As},
        {"With", ADT::Lang::TokenType::With},
        {"Arguments", ADT::Lang::TokenType::Arguments},
        {"To", ADT::Lang::TokenType::To},
        {"By", ADT::Lang::TokenType::By},
        {"From", ADT::Lang::TokenType::From},
        {"Returns", ADT::Lang::TokenType::Returns},
        {"Than", ADT::Lang::TokenType::Than},
        {"Then", ADT::Lang::TokenType::Then},
        {"Is", ADT::Lang::TokenType::Is},

        {"Declare", ADT::Lang::TokenType::Declare},
        {"Call", ADT::Lang::TokenType::Call},
        {"Add", ADT::Lang::TokenType::Add},
        {"Subtract", ADT::Lang::TokenType::Sub},
        {"Multiply", ADT::Lang::TokenType::Mul},
        {"Divide", ADT::Lang::TokenType::Div},
        {"Return", ADT::Lang::TokenType::Return},

        {"Greater", ADT::Lang::TokenType::Greater},
        {"If", ADT::Lang::TokenType::If},
        {"Else_If", ADT::Lang::TokenType::ElseIf},
        {"Else", ADT::Lang::TokenType::Else},
        {"Or", ADT::Lang::TokenType::Or},
        {"And", ADT::Lang::TokenType::And},
        {"Not", ADT::Lang::TokenType::Not},
        {"Equal", ADT::Lang::TokenType::Equal},
        {"Greater", ADT::Lang::TokenType::Greater},
        {"Less", ADT::Lang::TokenType::Less},

        {";", ADT::Lang::TokenType::Semicolon},
        {",", ADT::Lang::TokenType::Comma},

        {"True", ADT::Lang::TokenType::TrueLiteral},
        {"False", ADT::Lang::TokenType::FalseLiteral},

        {"String", ADT::Lang::TokenType::String},
        {"Float", ADT::Lang::TokenType::Float},
        {"Integer", ADT::Lang::TokenType::Integer},
        {"Boolean", ADT::Lang::TokenType::Boolean}
    };
}