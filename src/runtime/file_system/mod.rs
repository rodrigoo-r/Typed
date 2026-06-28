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
pub mod create_directory;
pub mod create_file;
mod file_exists;
pub mod file_name;
pub mod is_absolute_path;
pub mod is_directory;
pub mod is_file;
pub mod is_relative_path;
pub mod is_system_link;
pub mod join_path;
pub mod read_file;
pub mod scan_directory;
pub mod to_absolute_path;
pub mod write_file;

use crate::adt::lang::{ASTValue, Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();

    dict.insert(
        "Create_Directory",
        Procedure{
            ret: None,
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(create_directory::create_directory)
        }
    );

    dict.insert(
        "Create_File",
        Procedure{
            ret: None,
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(create_file::create_file)
        }
    );

    dict.insert(
        "File_Exists",
        Procedure{
            ret: Some(Kind::Boolean),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(file_exists::file_exists)
        }
    );

    dict.insert(
        "File_Name",
        Procedure{
            ret: Some(Kind::String),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(file_name::file_name)
        }
    );

    dict.insert(
        "Is_Absolute_Path",
        Procedure{
            ret: Some(Kind::Boolean),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(is_absolute_path::is_absolute_path)
        }
    );

    dict.insert(
        "Is_Directory",
        Procedure{
            ret: Some(Kind::Boolean),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(is_directory::is_directory)
        }
    );

    dict.insert(
        "Is_File",
        Procedure{
            ret: Some(Kind::Boolean),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(is_file::is_file)
        }
    );

    dict.insert(
        "Is_Relative_Path",
        Procedure{
            ret: Some(Kind::Boolean),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(is_relative_path::is_relative_path)
        }
    );

    dict.insert(
        "Is_System_Link",
        Procedure{
            ret: Some(Kind::Boolean),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(is_system_link::is_system_link)
        }
    );

    dict.insert(
        "Join_Path",
        Procedure{
            ret: Some(Kind::String),
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("paths")
                }
            ],
            variadic: false,
            body: None,
            native: Some(join_path::join_path)
        }
    );

    dict.insert(
        "Read_File",
        Procedure{
            ret: Some(Kind::String),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(read_file::read_file)
        }
    );

    dict.insert(
        "Scan_Directory",
        Procedure{
            ret: Some(Kind::List),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(scan_directory::scan_directory)
        }
    );

    dict.insert(
        "To_Absolute_Path",
        Procedure{
            ret: Some(Kind::String),
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                }
            ],
            variadic: false,
            body: None,
            native: Some(to_absolute_path::to_absolute_path)
        }
    );

    dict.insert(
        "Write_File",
        Procedure{
            ret: None,
            arguments: vec![
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("path")
                },
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("content")
                }
            ],
            variadic: false,
            body: None,
            native: Some(write_file::write_file)
        }
    );

    dict
}