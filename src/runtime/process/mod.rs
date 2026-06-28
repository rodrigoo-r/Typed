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
use crate::adt::lang::{ASTValue, Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub mod cwd;
pub mod exit;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();

    dict.insert(
        "Process_Cwd",
        Procedure{
            ret: None,
            arguments: vec![],
            variadic: false,
            body: None,
            native: Some(cwd::cwd)
        }
    );

    dict.insert(
        "Process_Exit",
        Procedure{
            ret: None,
            arguments: vec![
                Argument{
                    name: ASTValue::Borrowed("code"),
                    kind: Kind::Integer
                }
            ],
            variadic: false,
            body: None,
            native: Some(exit::exit)
        }
    );

    dict
}