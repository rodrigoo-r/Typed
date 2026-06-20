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
pub mod format;

use crate::adt::lang::{Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();
    dict.insert(
        "Format",
        Procedure{
            variadic: true,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: "fmt",
                        kind: Kind::String
                    }
                );

                args
            },
            native: Some(format::format_str)
        }
    );

    dict
}