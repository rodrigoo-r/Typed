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
pub mod access;
pub mod add;
pub mod size;
pub mod split;
pub mod trim_left;

use crate::adt::lang::{Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();
    dict.insert(
        "String_Format",
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
            native: Some(format::format)
        }
    );

    dict.insert(
        "String_Access",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: "s",
                        kind: Kind::String
                    }
                );

                args.push(
                    Argument{
                        name: "idx",
                        kind: Kind::Integer
                    }
                );

                args
            },
            native: Some(access::access)
        }
    );

    dict.insert(
        "String_Add",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: "s",
                        kind: Kind::String
                    }
                );

                args.push(
                    Argument{
                        name: "s2",
                        kind: Kind::String
                    }
                );

                args
            },
            native: Some(add::add)
        }
    );

    dict.insert(
        "String_Size",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: "s",
                        kind: Kind::String
                    }
                );

                args
            },
            native: Some(size::size)
        }
    );
    
    dict.insert(
        "String_Split",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: "s",
                        kind: Kind::String
                    }
                );
                
                args.push(
                    Argument{
                        name: "delim",
                        kind: Kind::String
                    }
                );

                args
            },
            native: Some(split::split)
        }
    );

    dict
}