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

pub mod print;
pub mod println;
pub mod read;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();
    dict.insert(
        "Print",
        Procedure{
            variadic: true,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: ASTValue::Borrowed("fmt"),
                        kind: Kind::String
                    }
                );

                args
            },
            ret: None,
            native: Some(print::print)
        }
    );

    dict.insert(
        "Print_Line",
        Procedure{
            variadic: true,
            body: None,
            arguments: {
                let mut args = vec![];
                args.push(
                    Argument{
                        name: ASTValue::Borrowed("fmt"),
                        kind: Kind::String
                    }
                );

                args
            },
            ret: None,
            native: Some(println::println)
        }
    );

    dict.insert(
        "Read_Line",
        Procedure{
            variadic: false,
            body: None,
            arguments: Vec::new(),
            native: Some(read::read),
            ret: None
        }
    );

    dict
}