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
#include "IsAbsolute.h"
#include "IsDirectory.h"
#include "IsFile.h"
#include "IsRelative.h"
#include "IsSymLink.h"
#include "ReadFile.h"
#include "ScanDirectory.h"
#include "ToAbsolute.h"

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
                ADT::Runtime::ObjectType::String,
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
            "Is_Absolute_Path",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                IsAbsolute
            }
        },
        {
            "Is_Directory",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                IsDirectory
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
            "Is_Relative_Path",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::Boolean,
                false,
                IsRelative
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
            "Join_Path",
            {
                {
                    {"p", ADT::Runtime::ObjectType::List}
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
                ADT::Runtime::ObjectType::String,
                false,
                ReadFile
            }
        },
        {
            "Scan_Directory",
            {
                {
                    {"p", ADT::Runtime::ObjectType::String}
                },
                nullptr,
                ADT::Runtime::ObjectType::List,
                false,
                ScanDirectory
            }
        },
        {
            "To_Absolute_Path",
            {
                {
                    {"p", ADT::Runtime::ObjectType::List}
                },
                nullptr,
                ADT::Runtime::ObjectType::String,
                false,
                ToAbsolute
            }
        }
    };
}