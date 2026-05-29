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

#pragma once
#include "ADT/Map/Procedure.h"
#include "CreateDirectory.h"
#include "CreateFile.h"
#include "Cwd.h"
#include "FileExists.h"
#include "IsFile.h"
#include "IsSymLink.h"
#include "ReadFile.h"

namespace Typed::Runtime::FileSystem
{
    inline ADT::Map::Procedure Package = {
        {
            "Create_Directory",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                CreateDirectory
            }
        },
        {
            "Create_File",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Void,
                false,
                CreateFile
            }
        },
        {
            "Process_Cwd",
            {
                {},
                nullptr,
                ADT::Runtime::ObjectType::OwnedString,
                false,
                Cwd
            }
        },
        {
            "File_Exists",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                FileExists
            }
        },
        {
            "Is_File",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                IsFile
            }
        },
        {
            "Is_System_Link",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                IsSymLink
            }
        },
        {
            "Read_File",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::OwnedString,
                false,
                ReadFile
            }
        }
    };
}