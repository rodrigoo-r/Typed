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
pub mod parse;

use crate::adt::lang::{ASTValue, Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();
    dict.insert(
        "YAML_Parse",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: ASTValue::Borrowed("source"),
                        kind: Kind::String
                    }
                );

                args
            },
            ret: Some(Kind::String),
            native: Some(parse::parse)
        }
    );

    dict
}