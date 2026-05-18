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
        {"As", ADT::Lang::TokenType::As},
        {"With", ADT::Lang::TokenType::With},
        {"Arguments", ADT::Lang::TokenType::Arguments},
        {"To", ADT::Lang::TokenType::To},
        {"Declare", ADT::Lang::TokenType::Declare},
        {"Call", ADT::Lang::TokenType::Call},
        {"Call_Method", ADT::Lang::TokenType::CallMethod},
        {"+", ADT::Lang::TokenType::Add},
        {"-", ADT::Lang::TokenType::Sub},
        {"*", ADT::Lang::TokenType::Mul},
        {"/", ADT::Lang::TokenType::Div},
        {"True", ADT::Lang::TokenType::TrueLiteral},
        {"False", ADT::Lang::TokenType::FalseLiteral}
    };
}